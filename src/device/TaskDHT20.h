#ifndef INC_TASKDHT20_H_
#define INC_TASKDHT20_H_

#include "globals.h"

#define delay_time_DHT 5000
#define MY_SCL 11
#define MY_SDA 12

extern void initDHT20();
extern void getValueDHT20();
extern float getValueDHT20_temp();
extern float getValueDHT20_humi();

#endif /* INC_TASKDHT20_H_ */