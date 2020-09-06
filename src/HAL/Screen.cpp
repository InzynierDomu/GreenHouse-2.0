#include "Screen.h"

namespace HAL{

Screen::Screen()
{
    Adafruit_SSD1306 display(Config::m_screen_width, Config::m_screen_height, &Wire);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
    { 
        Serial.println(F("SSD1306 allocation failed"));
    }
    else
    {
        Serial.println(F("SSD1306 allocation ok"));
    } 

    display.clearDisplay();
    display.setRotation(2);
    display.setTextSize(2);      
    display.setTextColor(SSD1306_WHITE); 
    display.display();
}

void Screen::Print(String text)
{
    // display.clearDisplay();
    // display.setCursor(0, 0);
    // display.println(text);
    // display.display();
}

}