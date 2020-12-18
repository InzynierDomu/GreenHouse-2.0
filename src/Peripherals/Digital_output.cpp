#include <PubSubClient.h>

#include "Logger.h"
#include "Digital_output.h"

namespace Peripherals{

Digital_output::Digital_output(HAL::GPIO_controller* controller, PubSubClient* client, int pin, String topic)
: m_controller(controller)
{
    m_logger = new Logger("Digital output (topic:" + topic + " pin:" + String(pin) + ")");
    m_pin = pin;
    m_topic = topic;
    
    char convert_buf[30];
    m_topic.toCharArray(convert_buf, 30);
    client->subscribe(convert_buf);
}

} //Peripherals
