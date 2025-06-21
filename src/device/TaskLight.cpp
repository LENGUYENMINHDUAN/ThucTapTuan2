#include "TaskLight.h"

void TaskLight(void *pvParameters)
{
    while (true)
    {
        getValueLight();
        vTaskDelay(delay_time_light / portTICK_PERIOD_MS);
    }
}

int LightGet()
{
    int light = digitalRead(LIGHT_PIN);
    return light;
}

void getValueLight()
{
    int lightValue = LightGet();
    Serial.print("Light sensor value: " + String(lightValue));
    publishData("Light_data", String(lightValue));
}

void initLight()
{
    pinMode(LIGHT_PIN, INPUT);
    Serial.println("Light sensor Initiate");
    xTaskCreate(TaskLight, "Task_light", 2048, NULL, 1, NULL);
}