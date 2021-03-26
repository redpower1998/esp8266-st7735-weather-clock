# ESP8266-ST7735-Weather-Clock

#### 介绍
基于ESP8266，ST7735 和Arduino 的自动天气预报，参考了ESP8266-ST7735-weather-station 项目。

#### 软件架构
软件架构说明
![接线图](https://images.gitee.com/uploads/images/2021/0326/080452_e6d8a2cb_335951.png "屏幕截图.png")

运行效果
![运行效果](https://images.gitee.com/uploads/images/2021/0326/081338_21b06cf9_335951.png "屏幕截图.png")
#### 安装教程

1.  安装Arduino，可以通过Windows10 的应用程序商店安装
2.  安装开发板（从开发板管理器安装）NodeMCU 1.0
3.  安装依赖库（从管理库安装）Adafruit_GFX 1.10.6
4.  安装依赖库（从管理库安装）Adafruit_ST7735  1.7.0
5.  安装依赖库（从管理库安装）ArduinoJson 5.10.1 
6.  修改代码中的ssid，password (wifi 热点和密码）
7.  修改APIKEY 和CityID。 这个请先在 openweathermap.org免费申请。 
8.  验证/编译
9.  上传到开发板

#### 使用说明

1.  依赖库的版本问题：安装教程中是我使用的版本。 更新或者更旧的版本没有测试过，但也许可以。
2.  如果你的开发板与我不同，那么接线可能不同，必须修改PinOut  
// PinOuts  
#define TFT_CS     D1  
#define TFT_RST    D2  
#define TFT_RS     D3     
#define TFT_SDI    D7     

