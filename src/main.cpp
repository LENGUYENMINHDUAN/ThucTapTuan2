
#include "globals.h"

void setup()
{
  Serial.begin(115200);
  Wire.begin(MY_SCL, MY_SDA);
  initWiFi();
  initMQTT();
  InitWebsever();

  initDHT20();
  initDistance();
  initMoisture();
  initLight();

  initFanRelay();
  initRGB();
  initLCD();
  // LiquidCrystal_I2C lcd(33, 16, 2);
  // lcd.begin();
}

void loop()
{
  // lcd.setCursor((16 - 5) / 2, 0);
  // lcd.print("Hello");
  // lcd.setCursor(0, 1);
  // lcd.print("My name is Tuan");
  // delay(5000);
  // lcd.clear();
  // delay(5000);
  if (!Wifi_reconnect())
  {
    return;
  }
  
  reconnectMQTT();
  WebSeverloop();
}