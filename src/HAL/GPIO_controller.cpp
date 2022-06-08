#include "GPIO_controller.h"

#include "Config.h"

namespace HAL
{

GPIO_controller::GPIO_controller(const int adress)
: m_adress(adress)
, m_exspander(Adafruit_MCP23X17())
{
  m_exspander.begin_I2C(adress, &Wire);
}

void GPIO_controller::set_in_out(const int type, const int pin)
{
  m_exspander.pinMode(pin, type);
}

uint8_t GPIO_controller::get_state(const int pin)
{
  return m_exspander.digitalRead(pin);
}

void GPIO_controller::turn_on_pin(const int pin)
{
  m_exspander.digitalWrite(pin, LOW);
}

void GPIO_controller::turn_off_pin(const int pin)
{
  m_exspander.digitalWrite(pin, HIGH);
}


int GPIO_controller::get_adress() const
{
  return m_adress;
}

} // namespace HAL