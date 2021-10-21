#ifndef PERIPHERALS_PERIPHERAL
#define PERIPHERALS_PERIPHERAL

#include <Arduino.h>

namespace Peripherals
{

class Peripheral
{
  public:
  virtual ~Peripheral() {}

  protected:
  String m_topic;
  int m_pin;
};

} // namespace Peripherals

#endif // PERIPHERALS_PERIPHERAL