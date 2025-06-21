#ifndef INC_TASKHUMIDITYDIRT_H_
#define INC_TASKHUMIDITYDIRT_H_

#include "globals.h"

#define delay_time_moisture 5000
#define SOIL_MOISTURE_PIN 1

extern void initMoisture();
extern void getMoisture();
extern int MoistureGet();

#endif /* INC_TASKHUMIDITYDIRT_H_ */