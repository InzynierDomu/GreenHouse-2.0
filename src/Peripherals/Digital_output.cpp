#include "Digital_output.h"

namespace Peripherals{

Digital_output::Digital_output(HAL::GPIO_controller* controller, int pin, char* topic)
: m_controller(controller)
{
    m_pin = pin;
    m_topic = topic;
}

} //Peripherals
