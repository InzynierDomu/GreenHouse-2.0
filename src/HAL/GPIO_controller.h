#include <Wire.h>
#include <Adafruit_MCP23017.h>

#ifndef HAL_GPIO_CONTROLLER
#define HAL_GPIO_CONTROLLER

namespace HAL{

class GPIO_controller
{
    GPIO_controller();
};
} //namespace HAL

#endif //HAL_GPIO_CONTROLLER