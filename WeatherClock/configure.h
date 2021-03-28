#ifndef CONFIGURE_HH
#define CONFIGURE_HH

//SSID and Password of your WiFi router
const char* ssid = "XXXXXXXXx";
const char* password = "XXXXXXXXXXX";


String APIKEY = "XXXXXXXXXXXXXXXXX"; //openweathermap.org APIkey
String CityID = "XXXXXXX";  //ID not name

const int timezone = 8;
int dst = 0;

// Pins
#define TFT_CS     D1
#define TFT_RST    D2
#define TFT_RS     D3  // AO
#define TFT_SDI    D7  

#endif
