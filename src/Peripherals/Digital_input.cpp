/**
 * @file Digital_input.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Digital input handling
 * @date 2022-06
 */

#include "Digital_input.h"

#include "HAL/Real_clock.h"

namespace Peripherals
{

/**
 * @brief Construct a new Digital_input::Digital_input object
 * @param controller: GPIO expander
 * @param pin: pin number
 * @param topic: mqtt topic to publish
 */
Digital_input::Digital_input(HAL::GPIO_controller* controller, const uint8_t pin, const String topic)
: m_controller(controller)
, m_logger(Logger("Digital input (topic:" + topic + " pin:" + String(pin) + ")", HAL::Real_clock::get_instance()->get_time_callback()))
, m_topic(topic)
, m_pin(pin)
{}

/**
 * @brief publish actual pin state
 * @param client: mqtt client 
 */
void Digital_input::publish(PubSubClient& client)
{
  char buf[1];
  uint8_t state = m_controller->get_state(m_pin);
  sprintf(buf, "%d", state);
  m_logger.log(buf);
  client.publish(m_topic.c_str(), buf);
}

} // namespace Peripherals
