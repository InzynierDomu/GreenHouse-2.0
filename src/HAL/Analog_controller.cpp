#include "Analog_controller.h"

#include "Config.h"
#include "Real_clock.h" 

namespace HAL
{

Analog_controller::Analog_controller(const int address)
: m_logger(Logger("Analog_controller", Real_clock::get_instance()->get_time_callback()))
, m_address(address)
, m_expander(PCF8591(address))
{

  m_expander.begin();
}

Analog_controller::~Analog_controller() {}

int Analog_controller::get_adress() const
{
  return m_address;
}

int Analog_controller::get_value(int pin)
{
  auto value = m_expander.analogRead(pin);
  return value;
}

} // namespace HAL