#include "Analog_controller.h"
#include "Config.h"

namespace HAL
{

Analog_controller::Analog_controller(int address):
m_address(address)
{
  m_logger = new Logger("Analog_controller");
  m_expander = new PCF8591(address);
  m_expander->begin();
  int test = m_expander->analogRead(1);
  m_logger->log(String(test));
}

Analog_controller::~Analog_controller()
{
}

int Analog_controller::get_adress()
{
  return m_address;
}

int Analog_controller::get_value(int pin)
{
  auto value = m_expander->analogRead(pin);
  return value;
}

} //namespace HAL