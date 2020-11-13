#include "GPIO_controller.h"

namespace HAL{

GPIO_controller::GPIO_controller(int adress):
m_adress(adress)
{
    m_exspander = new Adafruit_MCP23017();
}

bool GPIO_controller::read_state(int pin)
{
    m_exspander->readGPIO(pin);
}

void GPIO_controller::set_state(int pin, bool state)
{
    
}

int GPIO_controller::get_adress()
{
    return m_adress;
}

} //namespace HAL