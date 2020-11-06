#ifndef PERIPHERALS_PERIPHERALS_GENERATOR
#define PERIPHERALS_PERIPHERALS_GENERATOR

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <vector>

#include "Digital_output.h"
#include "Multisensor.h"
#include "HAL/Init.h"

namespace Peripherals{

class Peripherals_generator
{
public:
    Peripherals_generator(HAL::Init* hal, JsonDocument& json);
    ~Peripherals_generator();

    void publish(PubSubClient* client);

private:
    std::vector<Digital_output> m_digital_outputs;
    Multisensor* m_multisensor;

    // void add_peripherals();
    void add_multisensor(HAL::Init* hal, JsonDocument& json);
    void generate_digital_in_out(HAL::Init* hal, JsonDocument& json);
};    

} //Peripherals

#endif //PERIPHERALS_PERIPHERALS_GENERATOR