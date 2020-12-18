#ifndef PERIPHERALS_PERIPHERALS_GENERATOR
#define PERIPHERALS_PERIPHERALS_GENERATOR

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <vector>

#include "Digital_output.h"
#include "Digital_input.h"
#include "Multisensor.h"
#include "HAL/Init.h"

namespace Peripherals{

class Peripherals_generator
{
public:
    Peripherals_generator(HAL::Init* hal, JsonDocument& json, PubSubClient* client);
    void publish();

private:
    std::vector<Digital_output> m_digital_outputs;
    std::vector<Digital_input> m_digital_inputs;
    PubSubClient* m_client;
    Multisensor* m_multisensor;
    Digital_output* m_test_digi_out;

    void add_multisensor(HAL::Init* hal, JsonDocument& json);
    void generate_digital_in_out(HAL::Init* hal, JsonDocument& json);

    int convert_bin_to_dec(String number);
};    

} //Peripherals

#endif //PERIPHERALS_PERIPHERALS_GENERATOR