#ifndef PERIPHERALS_PERIPHERALS_GENERATOR
#define PERIPHERALS_PERIPHERALS_GENERATOR

#include <vector>

namespace Peripherals{

class Peripheral;

class Peripherals_generator
{
public:
    Peripherals_generator();
    ~Peripherals_generator();

private:
    const std::vector<Peripheral> m_outputs;

    void add_peripherals();
};    

} //Peripherals

#endif //PERIPHERALS_PERIPHERALS_GENERATOR