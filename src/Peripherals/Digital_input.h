#ifndef PERIPHERALS_DIGITAL_INPUT
#define PERIPHERALS_DIGITAL_INPUT

#include "Peripheral_input.h"
#include "HAL/GPIO_controller.h"

class Logger;

namespace Peripherals
{

class Digital_input : public Peripheral_input
{
public:
    Digital_input(HAL::GPIO_controller& controller, int pin, String topic);
    void publish(PubSubClient* client) override;

private:
    HAL::GPIO_controller& m_controller;
    Logger m_logger;
};

} //Peripherals

#endif //PERIPHERALS_DIGITAL_INPUT