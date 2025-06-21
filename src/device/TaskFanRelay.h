#ifndef INC_TASKFAN_H_
#define INC_TASKFAN_H_

#include "globals.h"

#define RELAY_PIN 8
#define FAN_PIN 10
#define delay_time_fan_relay 1000

extern void initFanRelay();
extern void loopFanRelay();
#endif /* INC_TASKFAN_H_ */