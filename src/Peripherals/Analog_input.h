#ifndef PERIPHERALS_ANALOG_INPUT
#define PERIPHERALS_ANALOG_INPUT

#include "Peripheral_input.h"
#include "HAL/Analog_controller.h"

class Logger;

namespace Peripherals
{

class Analog_input : public Peripheral_input
{
public:
    Analog_input(HAL::Analog_controller& controller, const int pin, const String topic);
    void publish(PubSubClient* client) override;

private:
    HAL::Analog_controller& m_controller;
    Logger m_logger;
};

}

#endif // PERIPHERALS_ANALOG_INPUT