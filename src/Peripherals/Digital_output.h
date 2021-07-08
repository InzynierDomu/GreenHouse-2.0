#ifndef PERIPHERALS_DIGITAL_OUTPUT
#define PERIPHERALS_DIGITAL_OUTPUT

#include "Peripheral_output.h"
#include "HAL/GPIO_controller.h"

class Logger;

namespace Peripherals{

class Digital_output : public Peripheral_output
{
public:
    Digital_output(HAL::GPIO_controller& controller, PubSubClient* client, int pin, String topic);
    void set_value(byte value) override;
    String get_topic();

private:
    HAL::GPIO_controller& m_controller;
    Logger* m_logger;
};

} //Peripherals

#endif //PERIPHERALS_DIGITAL_OUTPUT