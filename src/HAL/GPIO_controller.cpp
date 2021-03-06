#include "GPIO_controller.h"
#include "Config.h"

namespace HAL{

GPIO_controller::GPIO_controller(int adress):
m_adress(adress)
{
  m_exspander = new Adafruit_MCP23017();
  m_exspander->begin(adress - Config::min_adress_gpio_controllers);
}

void GPIO_controller::set_in_out(int type, int pin)
{
  m_exspander->pinMode(pin, type);
}

byte GPIO_controller::get_state(int pin)
{
  return m_exspander->digitalRead(pin);
}

void GPIO_controller::set_state(int pin, byte state)
{
  m_exspander->digitalWrite(pin, state);
}

int GPIO_controller::get_adress()
{
  return m_adress;
}

} //namespace HAL