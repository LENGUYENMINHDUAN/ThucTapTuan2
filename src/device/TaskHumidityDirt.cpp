#include "TaskHumidityDirt.h"

int soilValue = 0;

void TaskMoisture (void *pvParameters)
{
    while (true)
    {
        getMoisture();
        vTaskDelay(delay_time_moisture / portTICK_PERIOD_MS);
    }
}

int MoistureGet()
{
    soilValue = analogRead(SOIL_MOISTURE_PIN);
    return soilValue;
}

void getMoisture()
{
    int Moist = MoistureGet();
    Serial.print("Soil Moisture Raw Value: ");
    Serial.println(Moist);

    publishData("Moisture_Data", String(Moist));
}

void initMoisture()
{
    analogReadResolution(12);
    xTaskCreate(TaskMoisture, "Task_Moisture", 2048, NULL, 1, NULL);
}