#ifndef PERIPHERALS_DIGITAL_OUTPUT
#define PERIPHERALS_DIGITAL_OUTPUT

#include "Peripheral.h"
#include "HAL/GPIO_controller.h"

namespace Peripherals{

class Digital_output : public Peripheral
{
public:
    Digital_output(HAL::GPIO_controller* controller, int pin, char* topic);

private:
    const HAL::GPIO_controller* m_controller;
};

} //Peripherals

#endif //PERIPHERALS_DIGITAL_OUTPUT