#include "Digital_input.h"

namespace Peripherals{

Digital_input::Digital_input(HAL::GPIO_controller* controller, int pin, char* topic)
: m_controller(controller)
{
    m_pin = pin;
    m_topic = topic;
}

} //Peripherals
