#ifndef PERIPHERALS_DIGITAL_INPUT
#define PERIPHERALS_DIGITAL_INPUT

#include <PubSubClient.h>

#include "Peripheral.h"
#include "HAL/GPIO_controller.h"

namespace Peripherals{

class Digital_input : public Peripheral
{
public:
    Digital_input(HAL::GPIO_controller* controller, int pin, String topic);
    void publish(PubSubClient* client);

private:
    HAL::GPIO_controller* m_controller;
};

} //Peripherals

#endif //PERIPHERALS_DIGITAL_INPUT