#include <Wire.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Config.h"

#ifndef HAL_SCREEN
#define HAL_SCREEN

namespace HAL{
class Screen
{
public:
    Screen();
    void Print(String text);
private:
    
};  
} // namespace HAL

#endif // HAL_SCREEN
