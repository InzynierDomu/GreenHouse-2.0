#include "Digital_output.h"

namespace Peripherals{

Digital_output::Digital_output(GPIO_controller& controller, int pin, String topic)
: m_controller(controller)
{
    m_topic = topic;
    m_pin = pin;
}

Digital_output::~Digital_output()
{
}

} //Peripherals
