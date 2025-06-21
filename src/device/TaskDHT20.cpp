#include "TaskDHT20.h"


DHT20 dht20 (&Wire);

void TaskTemperatureHumidity(void *pvParameters)
{
    while (true)
    {
        getValueDHT20();
        vTaskDelay(delay_time_DHT / portTICK_PERIOD_MS);
    }
}

float getValueDHT20_temp() {
    float temp = dht20.getTemperature();
    return temp;
}

float getValueDHT20_humi() {
    float humi = dht20.getHumidity();
    return humi;
}

void getValueDHT20()
{
    if (dht20.read() == DHT20_OK)
    {
        Serial.println(String(dht20.getTemperature()) + "-" + String(dht20.getHumidity()));
        /////
        publishData("DHT20_data", "Temperature: " + String(dht20.getTemperature()) + "- Humidity: " + String(dht20.getHumidity()));
    }
    else
    {
        Serial.println("Failed to read DHT20 sensor.");
    }
}

void initDHT20()
{
    //Wire.begin(MY_SCL, MY_SDA);
    dht20.begin();
    xTaskCreate(TaskTemperatureHumidity, "Task_DHT20", 2048, NULL, 1, NULL);
}
