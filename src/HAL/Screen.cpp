#include "Screen.h"

namespace HAL{

Screen::Screen()
{
    Adafruit_SSD1306 display(Config::m_screen_width, Config::m_screen_height, &Wire);
    if(!display.begin(SSD1306_SWITCHCAPVCC, Config::m_screen_adress)) 
    { 
        Serial.println(F("Screen not founded"));
    }
    else
    {
        Serial.println(F("Screen founded"));
    } 

    display.clearDisplay();
    display.setRotation(2);
    display.setTextSize(2);  
    display.setTextColor(SSD1306_WHITE); 

    display.setCursor(0, 0);
    display.println("test");
    
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