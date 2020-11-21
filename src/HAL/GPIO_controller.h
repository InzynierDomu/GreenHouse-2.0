#ifndef HAL_GPIO_CONTROLLER
#define HAL_GPIO_CONTROLLER

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>

namespace HAL
{

class GPIO_controller
{
public:
    GPIO_controller(int adress);

    void set_in_out(int type, int pin);
    byte get_state(int pin);
    void set_state(int pin, byte state);
    int get_adress();

private:
    Adafruit_MCP23017* m_exspander;

    const int m_adress;
};
} //namespace HAL

#endif //HAL_GPIO_CONTROLLER