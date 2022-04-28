#ifndef HAL_ANALOG_CONTROLLER
#define HAL_ANALOG_CONTROLLER

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
  const int m_address;
  PCF8591 m_expander;
  Logger m_logger;
};

} // namespace HAL

#endif // HAL_ANALOG_CONTROLLER