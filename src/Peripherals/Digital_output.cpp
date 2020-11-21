#include <PubSubClient.h>

#include "Digital_output.h"

namespace Peripherals{

Digital_output::Digital_output(HAL::GPIO_controller* controller, PubSubClient* client, int pin, String topic)
: m_controller(controller)
{
    m_logger = new Logger("Digital output (topic:" + topic + ")");
    m_pin = pin;
    m_topic = topic;
    
    String name = "Create digital output on pin" + String(pin);
    m_logger->log(name, Msg_type::info);
    
    char convert_buf[30];
    m_topic.toCharArray(convert_buf, 30);
    client->subscribe(convert_buf);
}

} //Peripherals
