#include <PubSubClient.h>

#include "Logger.h"
#include "Digital_input.h"

namespace Peripherals{

Digital_input::Digital_input(HAL::GPIO_controller* controller, int pin, String topic)
: m_controller(controller)
{
  m_logger = new Logger("Digital input (topic:" + topic + " pin:" + String(pin) + ")");
  m_pin = pin;
  m_topic = topic;
}

void Digital_input::publish(PubSubClient* client)
{
  char topic[30];
  m_topic.toCharArray(topic, 30);
  uint8_t state = m_controller->get_state(m_pin);
  client->publish(topic, &state, 1);
} 

}//Peripherals
