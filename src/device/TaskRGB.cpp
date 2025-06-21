#include "TaskRGB.h"
int colorNumber = 0;
int RGBstateon;

Adafruit_NeoPixel rgb(1, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t colors[] = 
{
    rgb.Color(255, 0, 0),     // đỏ
    rgb.Color(255, 80, 0),    // cam
    rgb.Color(255, 255, 0),   // vàng
    rgb.Color(0, 255, 0),     // lục
    rgb.Color(0, 0, 255),     // lam
    rgb.Color(75, 0, 130),    // chàm
    rgb.Color(128, 0, 128),   // tím
    rgb.Color(255, 255, 255), // trắng
    rgb.Color(0, 0, 0)        // đen (tắt)
};

void TaskRGB(void *pvParameters)
{
    while (true)
    {
        if (rgbOn == true)
        {
            if (colorNumber <= 8) //after black -> return to red
            {
                colorNumber++;
            } 
            if (colorNumber > 8)
            {
                colorNumber = 0;
            }
            loopRGB();
        }
        else {
            RGBoff();
        }
        vTaskDelay(delay_time_RGB / portTICK_PERIOD_MS);
    }
}


void RGBoff()
{
    RGBstateon = 0;
    colorNumber=8;
    rgb.setPixelColor(0, colors[8]); //black = off
    rgb.show();
}

void loopRGB()
{
    // RGBstateon = 1;
    rgb.setPixelColor(0, colors[colorNumber]);
    rgb.show(); 
    
}

void initRGB()
{
    rgb.begin();
    rgb.show();
    RGBstateon = 1;
    xTaskCreate(TaskRGB, "Task_RGB", 2048, NULL, 1, NULL);
}