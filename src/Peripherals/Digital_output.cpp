#include "Digital_output.h"

#include "HAL/Real_clock.h"
#include "Logger.h"

namespace Peripherals
{

Digital_output::Digital_output(HAL::GPIO_controller& controller, PubSubClient& client, int pin, String topic, Scheduler* scheduler)
: m_controller(controller)
, m_logger(new Logger("Digital output (topic:" + topic + " pin:" + String(pin) + ")", HAL::Real_clock::get_instance()->get_time_callback()))
, m_scheduler(scheduler)
{
  m_pin = pin;
  m_topic = topic;

  m_controller.set_in_out(OUTPUT, m_pin);

  char convert_buf[30];
  m_topic.toCharArray(convert_buf, 30);
  client.subscribe(convert_buf);
}

void Digital_output::turn_off()
{
  m_controller.set_state(m_pin, 0);
  m_logger->log("turn off");
}

void Digital_output::set_value(uint8_t value)
{
  value -= 48;
  if (value < 2)
  {
    m_controller.set_state(m_pin, value);
    if (value)
    {
      m_logger->log("turn on");
    }
    else
    {
      m_logger->log("turn off");
    }
  }
  else
  {
    m_scheduler->add_action([this]() { turn_off(); }, value - 1); //todo: error, probably main 71: move m_peripherals is a problem with move and correct address
    m_logger->log("turn on for " + String(value - 1) + "s");
  }
}

String Digital_output::get_topic()
{
  return m_topic;
}

} // namespace Peripherals
