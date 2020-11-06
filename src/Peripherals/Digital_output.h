#ifndef PERIPHERALS_DIGITAL_OUTPUT
#define PERIPHERALS_DIGITAL_OUTPUT

#include "Peripheral.h"

namespace Peripherals{

class GPIO_controller;

class Digital_output : public Peripheral
{
public:
    Digital_output(GPIO_controller& controller, int pin, char* topic);
    ~Digital_output();

private:
    const GPIO_controller& m_controller;
};

} //Peripherals

#endif //PERIPHERALS_DIGITAL_OUTPUT