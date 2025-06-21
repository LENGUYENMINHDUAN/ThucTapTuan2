#ifndef INC_TASKLCD_H_
#define INC_TASKLCD_H_

#include "globals.h"

#define delay_time_LCD 5000
extern LiquidCrystal_I2C lcd;

extern void initLCD();
extern void showValueLCD();

#endif /* INC_TASKLCD_H_ */