#ifndef GLOBALS_H
#define GLOBALS_H

// include libraries
#include <Wire.h>
#include <WiFi.h>
#include <DHT20.h>
#include <PubSubClient.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include <UltraSonic.h>

///
#include "../src/connect/TaskWifi.h"
#include "../src/connect/TaskMQTT.h"
#include "../src/connect/TaskWebserver.h"

#include "../src/device/TaskDHT20.h"
#include "../src/device/TaskHumidityDirt.h"
#include "../src/device/TaskDistance.h"
#include "../src/device/TaskFanRelay.h"
#include "../src/device/TaskLight.h"
#include "../src/device/TaskRGB.h"
#include "../src/device/TaskLCD.h"


#endif