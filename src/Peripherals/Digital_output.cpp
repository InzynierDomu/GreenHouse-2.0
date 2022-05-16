#include "Digital_output.h"

#include "HAL/Real_clock.h"
#include "Logger.h"

namespace Peripherals
{

Digital_output::Digital_output(HAL::GPIO_controller& controller, PubSubClient& client, int pin, String topic)
: m_controller(controller)
, m_logger(new Logger("Digital output (topic:" + topic + " pin:" + String(pin) + ")", HAL::Real_clock::get_instance()->get_time_callback()))
{
  m_pin = pin;
  m_topic = topic;

  m_controller.set_in_out(OUTPUT, m_pin);

  char convert_buf[30];
  m_topic.toCharArray(convert_buf, 30);
  client.subscribe(convert_buf);
}

void Digital_output::set_value(uint8_t value)
{
  m_logger->log("value seted");
  m_logger->log(String(value));
  // TODO: for test
  m_controller.set_state(m_pin, value - 48);
}

String Digital_output::get_topic()
{
  return m_topic;
}

} // namespace Peripherals
