#include <Wire.h>
#include <Adafruit_MCP23017.h>

#ifndef HAL_GPIO_CONTROLLER
#define HAL_GPIO_CONTROLLER

namespace HAL
{

class GPIO_controller
{
public:
    GPIO_controller(int adress);

    bool read_state(int pin);
    void set_state(int pin, bool state);
    int get_adress();

private:
    Adafruit_MCP23017* m_exspander;

    const int m_adress;
};
} //namespace HAL

#endif //HAL_GPIO_CONTROLLER