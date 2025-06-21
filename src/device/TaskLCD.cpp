#include "TaskLCD.h"

float temp = 0;
float humi = 0;
int moisture = 0;
int light = 0;
float dist = 0;

LiquidCrystal_I2C lcd(33, 16, 2); 
void TaskLCD(void *pvParameters)
{
    while (true)
    {
        showValueLCD();
        vTaskDelay(delay_time_LCD / portTICK_PERIOD_MS);
        // lcd.setCursor((16 - 5) / 2, 0);
        // lcd.print("Hello");
        // lcd.setCursor(0, 1);
        // lcd.print("My name is Tuan");
        // delay(5000);
        // lcd.clear();
        // delay(5000);
    }
}

// void getSensorValue()
// {
//     //temp = getValueDHT20_temp();
//     // humi = getValueDHT20_humi();
//     // moisture = MoistureGet();
//     // light = LightGet();
//     // dist = DistanceCalculate();
// }


void showValueLCD()
{
    // DHT20
    // getSensorValue();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Nhiet do: ");
    temp = getValueDHT20_temp();
    lcd.print(temp, 1);
    lcd.print(" C");
    delay(delay_time_LCD);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Do am: ");
    humi = getValueDHT20_humi();
    lcd.print(humi, 1);
    lcd.print(" %");
    delay(delay_time_LCD);

    // HumidityDirt and Light
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Do am dat: ");
    moisture = MoistureGet();
    lcd.print(moisture);
    delay(delay_time_LCD);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Anh sang: ");
    light = LightGet();
    lcd.print(light);
    delay(delay_time_LCD);

    // --------- 3. Hiển thị khoảng cách ----------
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Khoang cach: ");
    lcd.setCursor(0, 1);
    dist = DistanceCalculate();
    lcd.print(dist, 1);
    lcd.print(" cm");
}

void initLCD()
{
    Wire.begin();            
    lcd.backlight(); 
    lcd.begin();
    xTaskCreate(TaskLCD, "Task_LCD", 2048, NULL, 1, NULL);
}