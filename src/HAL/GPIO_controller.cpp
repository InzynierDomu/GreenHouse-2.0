#include "GPIO_controller.h"

#include "Config.h"


namespace HAL
{

GPIO_controller::GPIO_controller(const int adress)
: m_adress(adress)
, m_exspander(Adafruit_MCP23017())
{
  m_exspander.begin(adress - Config::min_adress_gpio_controllers);
}

void GPIO_controller::set_in_out(const int type, const int pin)
{
  m_exspander.pinMode(pin, type);
}

byte GPIO_controller::get_state(const int pin)
{
  return m_exspander.digitalRead(pin);
}

void GPIO_controller::set_state(const int pin, const byte state)
{
  m_exspander.digitalWrite(pin, state);
}

int GPIO_controller::get_adress() const
{
  return m_adress;
}

} // namespace HAL