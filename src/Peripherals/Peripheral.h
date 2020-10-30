#ifndef PERIPHERALS_PERIPHERAL
#define PERIPHERALS_PERIPHERAL

#include <Arduino.h>

namespace Peripherals{

class Peripheral
{
public:
    Peripheral();
    ~Peripheral();

protected:
    String m_topic;
    int m_pin;
};

} //Peripherals

#endif //PERIPHERALS_PERIPHERAL