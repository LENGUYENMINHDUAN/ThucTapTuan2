#include "TaskDistance.h"

long duration;
float distance;

// Ultrasonic ultrasonic;

void TaskDistance(void *pvParameters)
{
    Ultrasonic ultrasonic(ECHO_PIN, TRIG_PIN);
    while (1)
    {
        Serial.println("Distance here: " + String(ultrasonic.read()) + " cm");
        vTaskDelay(delay_time_distance / portTICK_PERIOD_MS);
    }
}

float DistanceCalculate()
{
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);

    distance = duration * 0.034 / 2; //distance = (speed × time) / 2

    return distance;
}

void getValueDistance()
{
    float dist = DistanceCalculate();
    if (dist <= 0 || dist > 400) 
    {
        Serial.println("Distance sensor reading failed!");
    } else {
        Serial.print("Distance: " + String(dist) + " cm");
        publishData("Distance_data", String(dist));
    }
}

void initDistance()
{
    // Ultrasonic ultrasonic(ECHO_PIN, TRIG_PIN);
    Serial.println("Distance sensor Initiate");
    xTaskCreate(TaskDistance, "Task_Distance", 2048, NULL, 1, NULL);
}