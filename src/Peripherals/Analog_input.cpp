/**
 * @file Analog_input.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Analog input handling
 * @date 2022-06
 */

#include "Analog_input.h"

#include "HAL/Real_clock.h"
#include "Logger.h"

namespace Peripherals
{

/**
 * @brief Construct a new Analog_input::Analog_input object
 * @param controller: analog expander
 * @param pin: pin number
 * @param topic: mqtt topic to publish
 */
Analog_input::Analog_input(HAL::Analog_controller* controller, const uint8_t pin, const String& topic)
: m_controller(controller)
, m_logger(Logger("Analog input (topic:" + topic + " pin:" + String(pin) + ")", HAL::Real_clock::get_instance()->get_time_callback()))
, m_topic(topic)
, m_pin(pin)
{}

/**
 * @brief publish actual analog measurment value on pin
 * @param client: mqtt client
 */
void Analog_input::publish(PubSubClient& client)
{
  char buf[4];
  int value = m_controller->get_value(m_pin);
  sprintf(buf, "%d", value);
  m_logger.log(String(value));
  client.publish(m_topic.c_str(), buf);
}

} // namespace Peripherals