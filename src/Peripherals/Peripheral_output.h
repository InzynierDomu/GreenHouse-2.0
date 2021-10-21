#ifndef PERIPHERALS_PERIPHERAL_OUTPUT
#define PERIPHERALS_PERIPHERAL_OUTPUT

#include "Peripheral.h"

namespace Peripherals
{

class Peripheral_output : public Peripheral
{
  public:
  virtual ~Peripheral_output() {}
  virtual void set_value(byte value) = 0;

  protected:
  String m_topic;
  int m_pin;
};

} // namespace Peripherals

#endif // PERIPHERALS_PERIPHERAL_INPUT