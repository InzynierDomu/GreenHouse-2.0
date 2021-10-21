#ifndef PERIPHERALS_PERIPHERAL_INPUT
#define PERIPHERALS_PERIPHERAL_INPUT

#include "Peripheral.h"

namespace Peripherals
{

class PubSubClien;

class Peripheral_input : public Peripheral
{
  public:
  virtual ~Peripheral_input() {}
  virtual void publish(PubSubClient* client) = 0;

  protected:
  String m_topic;
  int m_pin;
};

} // namespace Peripherals

#endif // PERIPHERALS_PERIPHERAL_INPUT