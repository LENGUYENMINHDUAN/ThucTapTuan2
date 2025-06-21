#ifndef INC_TASKRGB_H_
#define INC_TASKRGB_H_

#include "globals.h"

#define LED_PIN 6
#define delay_time_RGB 1000
extern int colorNumber;
// extern int RGBstateon;
extern Adafruit_NeoPixel rgb;//(1, LED_PIN, NEO_GRB + NEO_KHZ800);
extern uint32_t colors[];

// extern void TaskRGB(void *pvParameters);
extern void RGBoff();
extern void initRGB();
extern void loopRGB();

#endif /* INC_TASKRGB_H_ */