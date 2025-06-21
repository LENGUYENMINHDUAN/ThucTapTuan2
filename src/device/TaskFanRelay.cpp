#include "TaskFanRelay.h"

void TaskFanRelay(void *pvParameters)
{
    while (true)
    {
        loopFanRelay();
        vTaskDelay(delay_time_fan_relay / portTICK_PERIOD_MS);
    }
}

void loopFanRelay() {
    //Serial.println("Relay ON");
    digitalWrite(RELAY_PIN, HIGH);
    delay(1000);

    //Serial.println("Relay OFF");
    digitalWrite(RELAY_PIN, LOW);
    delay(1000);

    //Serial.println("Fan ON");
    digitalWrite(FAN_PIN, HIGH);
    delay(1000);

    //Serial.println("Fan OFF");
    digitalWrite(FAN_PIN, LOW);
}

void initFanRelay()
{
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(FAN_PIN, LOW);
    xTaskCreate(TaskFanRelay, "Task_fan_Relay", 2048, NULL, 1, NULL);
}