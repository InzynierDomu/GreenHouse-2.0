#include "Analog_controller.h"

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

} //namespace HAL