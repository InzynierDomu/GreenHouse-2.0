#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Config.h"

namespace HAL{
class Screen
{
public:
    Screen();
    void Print(String text);
private:
    
};  
} // namespace HAL