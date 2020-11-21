#ifndef PERIPHERALS_DIGITAL_OUTPUT
#define PERIPHERALS_DIGITAL_OUTPUT

#include "Peripheral.h"
#include "HAL/GPIO_controller.h"
#include "Logger.h"

namespace Peripherals{

class Digital_output : public Peripheral
{
public:
    Digital_output(HAL::GPIO_controller* controller, PubSubClient* client, int pin, String topic);

private:
    HAL::GPIO_controller* m_controller;
    Logger* m_logger;
};

} //Peripherals

#endif //PERIPHERALS_DIGITAL_OUTPUT