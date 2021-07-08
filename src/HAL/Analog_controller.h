#ifndef HAL_ANALOG_CONTROLLER
#define HAL_ANALOG_CONTROLLER

#include <Arduino.h>
#include <PCF8591.h>

#include "Logger.h" 

namespace HAL
{

class Analog_controller
{
public:
  Analog_controller(int address);
  ~Analog_controller();
  int get_adress();
  int get_value(int pin);

private:
  PCF8591* m_expander;
  Logger* m_logger;

  const int m_address;
};

}//namespace HAL

#endif //HAL_ANALOG_CONTROLLER