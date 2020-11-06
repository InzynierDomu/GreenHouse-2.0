#ifndef PERIPHERALS_PERIPHERAL
#define PERIPHERALS_PERIPHERAL

#include <Arduino.h>

namespace Peripherals
{

class Peripheral
{
public:
    Peripheral();

protected:
    char* m_topic;
    int m_pin;
};

} //Peripherals

#endif //PERIPHERALS_PERIPHERAL