#ifndef INC_TASKLIGHT_H_
#define INC_TASKLIGHT_H_

#include "globals.h"

#define LIGHT_PIN A1
#define delay_time_light 5000

extern void initLight();
extern void getValueLight();
extern int LightGet();

#endif /* INC_TASKLIGHT_H_ */