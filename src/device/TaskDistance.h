#ifndef INC_TASKDISTANCE_H_
#define INC_TASKDISTANCE_H_

#include "globals.h"

//D10 D9
#define TRIG_PIN 21  
#define ECHO_PIN 18  

#define delay_time_distance 5000

extern void initDistance();
extern void getValueDistance();
extern float DistanceCalculate();

#endif /* INC_TASKDISTANCE_H_ */