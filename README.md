# ESP8266-ST7735-Weather-Clock

[中文在最后]

#### Introduction 
The automatic weather forecast based on ESP8266 and ST7735 refers to the ESP8266-ST7735-weather-station project. 

#### 软件架构
Architecture description 
![Wiring diagram ](https://images.gitee.com/uploads/images/2021/0326/080452_e6d8a2cb_335951.png "屏幕截图.png")

running result 
![running result ](https://images.gitee.com/uploads/images/2021/0328/175526_1bd8c44e_335951.png "屏幕截图.png")

#### Installation tutorial 

1. Install the Arduino IDE, which can be installed through the Windows 10 application store (only IDE is used, the hardware does not require Arduino)
2. Install the development board (install from the development board manager) NodeMCU 1.0
3. Install the dependent library (install from the management library) Adafruit_GFX 1.10.6
4. Install the dependent library (install from the management library) Adafruit_ST7735 1.7.0
5. Install the dependent library (install from the management library) ArduinoJson 5.10.1
6. Modify the ssid, password (wifi hotspot and password) in the configure.h header file
7. Modify APIKEY and CityID in configure.h header file. Please apply for this for free at openweathermap.org.
8. Verification/Compile
9. Upload to the development board 

#### Instructions for use 

1. The version of the dependent library: the version I used in the installation tutorial. Newer or older versions have not been tested, but it may be possible.  
2. If your development board is different from mine, then the wiring may be different, you must modify the Pins (in configure.h)   
// Pins  
#define TFT_CS     D1  
#define TFT_RST    D2  
#define TFT_RS     D3     
#define TFT_SDI    D7     


#### Agreement
Mulan License, Version 2 

#### 介绍
基于ESP8266，ST7735的自动天气预报，参考了ESP8266-ST7735-weather-station 项目。

#### 软件架构
软件架构说明
![接线图](https://images.gitee.com/uploads/images/2021/0326/080452_e6d8a2cb_335951.png "屏幕截图.png")

运行效果
![运行效果](https://images.gitee.com/uploads/images/2021/0328/175526_1bd8c44e_335951.png "屏幕截图.png")

#### 安装教程

1.  安装Arduino IDE，可以通过Windows10 的应用程序商店安装  （只用了IDE，硬件不需要Arduino）
2.  安装开发板（从开发板管理器安装）NodeMCU 1.0
3.  安装依赖库（从管理库安装）Adafruit_GFX 1.10.6
4.  安装依赖库（从管理库安装）Adafruit_ST7735  1.7.0
5.  安装依赖库（从管理库安装）ArduinoJson 5.10.1 
6.  修改configure.h 头文件中的ssid，password (wifi 热点和密码）
7.  修改configure.h 头文件中的 APIKEY 和CityID。 这个请先在 openweathermap.org免费申请。 
8.  验证/编译
9.  上传到开发板

#### 使用说明

1.  依赖库的版本问题：安装教程中是我使用的版本。 更新或者更旧的版本没有测试过，但也许可以。
2.  如果你的开发板与我不同，那么接线可能不同，必须修改Pins（在configure.h)   
// Pins  
#define TFT_CS     D1  
#define TFT_RST    D2  
#define TFT_RS     D3     
#define TFT_SDI    D7     


#### 许可协议
木兰宽松许可证, 第2版