#pragma once

#include "Logger.h"

#include <PCF8591.h>

namespace HAL
{

class Analog_controller
{
  public:
  Analog_controller(const int address);
  ~Analog_controller();
  int get_adress() const;
  int get_value(int pin);

  private:
  Logger m_logger;
  const int m_address;
  PCF8591 m_expander;
};

} // namespace HAL