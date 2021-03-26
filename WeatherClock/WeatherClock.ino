//代码是临时拼凑的，并没有检查，没有删除无用代码，甚至没有格式化。所以代码质量凑合看吧。 
// 代码发布在https://gitee.com/redpower/esp8266-st7735-weather-clock  
// ArduinoJson 5.10.1 是需要的
// Adafruit_GFX 1.10.6
/// Adafruit_ST7735  1.7.0
// 开发板 NodeMCU 1.0  ESP-12E  显示屏1.4TFT
// 波特率115200

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <time.h>
#include <Ticker.h>

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <math.h>

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

#include <Fonts/Tiny3x3a2pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/TomThumb.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/Org_01.h>
#include <Fonts/FreeSansBoldOblique24pt7b.h>

#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define TFT_PINK        0xFC9F


//SSID and Password of your WiFi router
const char* ssid = "XXXXXXX";
const char* password = "XXXXXXXXX";

String APIKEY = "XXXXXXXXXXXXX"; //openweathermap.org
String CityID = "XXXXXXX";  //注意是id，不是name

const int timezone = 8;
int dst = 0;

// PinOuts
#define TFT_CS     D1
#define TFT_RST    D2
#define TFT_RS     D3   //RS AO
#define TFT_SDI    D7    //SDI

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_RS, TFT_RST); // uses RGB565

WiFiClient client;    // WIFI Client
char servername[] = "api.openweathermap.org";  // remote server we will connect to
String result;

// set of variables used into this sketch for different pourpose
boolean   night = false;
String    timeS = "";
String    day = "";
int       weatherID = 0;
String    location = "";
String    temperature = "";
String    weather = "";
String    description = "";
String    idString = "";
String    umidityPer = "";
float     Fltemperature = 0;
int       counter = 30;
String    windS = "";
String    pressure = "";
String    Visibility = "";
String    Wind_angle = "";
String    Clouds = "";


void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  pinMode(TFT_SDI, OUTPUT);
  analogWrite(TFT_SDI, 50);
  lcd_init();

  configTime(timezone * 3600, 0, "pool.ntp.org"); //19800 (utc/gmt offset, daylight saving offset, ntp server)
  Serial.println("\nWaiting for time sync");
  while (!time(nullptr))
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Synced");
  tft.fillScreen(ST77XX_BLACK);
}



void lcd_init()
{
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  delay(200);
  tft.setRotation(tft.getRotation() + 2);

  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_WHITE);
  tft.setTextWrap(true);
  tft.println("System Init...");

  WiFi.begin(ssid, password);     //Connect to your WiFi router

  // Wait for connection
  tft.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    tft.print(".");
    delay(1000);
  }

  //If connection successful show IP address in serial monitor
  tft.println("");
  tft.println("Connected @ IP:");
  tft.println(WiFi.localIP());  //IP address assigned to your ESP
  tft.setFont(&FreeSans12pt7b);

}


void clockDisplay()
{
  static int old_day;
  static int old_min;
  char buf[9];
  String displayTime;
  //tft.fillScreen(ST77XX_BLACK);
  time_t now = time(nullptr);

  struct tm * timeinfo;
  timeinfo = localtime (&now);
  tft.setFont();
  tft.setCursor(20, 18);
  tft.setTextColor(ST7735_WHITE, 0x0000);
  tft.setFont(&FreeSans9pt7b);
  if (old_day != timeinfo->tm_mday)
  {
    old_day = timeinfo->tm_mday;
    tft.fillRect(0, 00, 128, 49, ST77XX_BLACK);
  }
  sprintf(buf, "%04d-%02d-%02d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
  displayTime = buf;
  tft.println(displayTime);
  Serial.println(displayTime);

  tft.drawFastHLine(0, 50, 128, ST77XX_GREEN); 
  
  if (old_min != timeinfo->tm_min)
  {
    old_min = timeinfo->tm_min;
    tft.fillRect(0, 25, 128, 25, ST77XX_BLACK);
  }
  tft.fillRect(80, 25, 40, 25, ST77XX_BLACK);
  sprintf(buf, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
  displayTime = buf;
  tft.setCursor(20, 42);
  tft.setTextColor(ST7735_YELLOW);
  tft.setFont(&FreeSans12pt7b);
  tft.println(displayTime);
  Serial.println(displayTime);

}


// get Weather data from openweathermap.org
// sent request for data
void getWeatherData() { //client function to send/receive GET request data.
  if (client.connect(servername, 80)) {  //starts client connection, checks for connection
    client.println("GET /data/2.5/weather?units=metric&id=" + CityID + "&APPID=" + APIKEY);
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
    return;
  }
  Serial.println("===>Connect.....");
  // reading sent data
  int count = 0;
  while (client.connected() && !client.available()) {
    count++;
    delay(10);
    if (count > 1000)
      return;
  }
  Serial.println("Waiting for data");
  while (client.connected() || client.available()) { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
    result = result + c;
  }

  // replacing character '['
  client.stop(); //stop client
  result.replace('[', ' ');
  result.replace(']', ' ');

  Serial.println(result);

  // format received data into a jsonArray.
  // to make this code working it has been becessary to install version
  char jsonArray [result.length() + 1];
  result.toCharArray(jsonArray, sizeof(jsonArray));
  jsonArray[result.length() + 1] = '\0';
  StaticJsonBuffer<1024> json_buf;
  JsonObject &root = json_buf.parseObject(jsonArray);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return ;
  }

  //TODO : try to understand why this double assignement is necessary
  String temperatureLOC = root["main"]["temp"];
  String weatherLOC = root["weather"]["main"];
  String descriptionLOC = root["weather"]["description"];
  String idStringLOC = root["weather"]["id"];
  String umidityPerLOC = root["main"]["humidity"];
  String windLOC = root["wind"]["speed"];
  String pressureLOC = root["main"]["pressure"];
  String visibilityLOC = root["visibility"];
  String wind_angleLOC = root["wind"]["deg"];
  String cloudsLOC = root ["clouds"]["all"] ;//["main"]
  String temp_max =  root["main"]["temp_max"];
  String temp_min =  root["main"]["temp_min"];

  String sunrise =  root["sys"]["sunrise"];
  String sunset =  root["sys"]["sunset"];
  String city_name =  root["name"];
  time_t sun_time = sunrise.toInt();
  char buf[6];
  struct tm * timeinfo = localtime (&sun_time);
  sprintf(buf, "%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
  sunrise = buf;

  sun_time = sunset.toInt();
  timeinfo = localtime (&sun_time);
  sprintf(buf, "%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
  sunset = buf;

  temperature = temperatureLOC;
  weather = weatherLOC;
  description = descriptionLOC;
  idString = idStringLOC;
  umidityPer = umidityPerLOC;
  windS = windLOC;
  pressure = pressureLOC;
  Visibility = visibilityLOC;
  Wind_angle = wind_angleLOC;
  Clouds = cloudsLOC;

  int length = temperature.length();
  if (length == 5) {
    temperature.remove(length - 3);
  }

  Fltemperature = temperature.toFloat();
  Fltemperature = Fltemperature - 273, 15;

  weatherID = idString.toInt();
  Serial.println(temperature);

  tft.fillRect(0, 52, 128, 76, TFT_NAVY);
  tft.setCursor(0, 58);
  tft.setFont();
  tft.setTextColor(ST7735_YELLOW);

  tft.println("Temp:" + temperature);
  tft.println("From:" + temp_min + " To:" + temp_max);
  tft.println("Weather:" + weather);
  tft.println("Desc:" + description);
  tft.println("Wind:" + Wind_angle + " Speed:" + windLOC);
  tft.println("Clouds:" + Clouds + " Visi:" + Visibility);
  tft.println("Humidity:" + umidityPerLOC);
  tft.println("Sun:" + sunrise + " - " + sunset);
  tft.setTextColor(ST7735_GREEN);
  tft.println(city_name);
}

void loop()
{
  int count = 15 * 60;
  if (weatherID == 0 )
  {
    count = 10;
  }
  for (int i = 0; i < count; i++)
  {
    clockDisplay();
    delay(1000);
  }
  tft.fillRect(0, 0, 128, 49, ST77XX_BLACK);
  tft.setCursor(20, 18);
  tft.setTextColor(TFT_MAGENTA);
  tft.println("Update...");
  getWeatherData();
  tft.fillRect(0, 0, 128, 49, ST77XX_BLACK);
  clockDisplay();
}