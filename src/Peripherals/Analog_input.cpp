#include <PubSubClient.h>

#include "Logger.h"
#include "Analog_input.h"

namespace Peripherals
{

Analog_input::Analog_input(HAL::Analog_controller& controller, const int pin, const String topic)
: m_controller(controller)
, m_logger(Logger("Analog input (topic:" + topic + " pin:" + String(pin) + ")"))
{
    m_pin = pin;
    m_topic = topic;
}

void Analog_input::publish(PubSubClient* client)
{
  char buf[4];
  String topic = m_topic;
  int value = m_controller.get_value(m_pin);
	sprintf(buf, "%d", value);
	m_logger.log(String(value), Log_type::debug);
  client->publish(topic.c_str(), buf);
}

}