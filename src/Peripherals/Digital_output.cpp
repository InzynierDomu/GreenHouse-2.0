/**
 * @file Digital_output.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Digital output handling
 * @date 2022-06
 */

#include "Digital_output.h"

#include "HAL/Real_clock.h"
#include "Logger.h"

namespace Peripherals
{

/**
 * @brief Construct a new Digital_output::Digital_output object
 * @param controller: GPIO expander
 * @param client: MQTT client
 * @param pin: pin number
 * @param topic: mqtt topic to subscribe
 * @param scheduler: event scheduler
 */
Digital_output::Digital_output(HAL::GPIO_controller* controller, PubSubClient& client, const uint8_t pin, const String& topic,
                               Scheduler& scheduler)
: m_controller(controller)
, m_logger(new Logger("Digital output (topic:" + topic + " pin:" + String(pin) + ")", HAL::Real_clock::get_instance()->get_time_callback()))
, m_scheduler(scheduler)
, m_topic(topic)
, m_pin(pin)
{
  m_controller->set_in_out(OUTPUT, m_pin);

  char convert_buf[30];
  m_topic.toCharArray(convert_buf, 30);
  client.subscribe(convert_buf);
}

/**
 * @brief set value on output pin
 * @param value: turn on, of or turn on for some time
 */
void Digital_output::set_value(const uint8_t value)
{
  if (value < 2)
  {
    if (value)
    {
      m_logger->log("turn on");
      m_controller->turn_on_pin(m_pin);
    }
    else
    {
      m_controller->turn_off_pin(m_pin);
      m_logger->log("turn off");
    }
  }
  else
  {
    m_controller->turn_on_pin(m_pin);
    m_scheduler.add_action([this]() { turn_off(); }, value - 1);
    m_logger->log("turn on for " + String(value - 1) + "s");
  }
}

/**
 * @brief get output topic
 * @return String topic
 */
String Digital_output::get_topic() const
{
  return m_topic;
}

void Digital_output::turn_off()
{
  m_controller->turn_off_pin(m_pin);
  m_logger->log("turn off");
}

} // namespace Peripherals
