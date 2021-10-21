#ifndef PERIPHERALS_DIGITAL_OUTPUT
#define PERIPHERALS_DIGITAL_OUTPUT

#include "HAL/GPIO_controller.h"
#include "Peripheral_output.h"


class Logger;

namespace Peripherals
{

class Digital_output : public Peripheral_output
{
  public:
  Digital_output(HAL::GPIO_controller& controller, PubSubClient* client, int pin, String topic);
  void set_value(byte value) override;
  String get_topic();

  private:
  HAL::GPIO_controller& m_controller;
  Logger* m_logger;
};

} // namespace Peripherals

#endif // PERIPHERALS_DIGITAL_OUTPUT