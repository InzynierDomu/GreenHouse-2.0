#include "Peripherals_generator.h"
#include "Peripheral.h"

namespace Peripherals{

Peripherals_generator::Peripherals_generator(HAL::Init* hal, JsonDocument& json)
{
    // int peripherals_count = array;
    // String type_peripherals;

    add_multisensor(hal, json);
    generate_digital_in_out(hal, json);
}
    
Peripherals_generator::~Peripherals_generator()
{
}

void Peripherals_generator::publish(PubSubClient* client)
{
    m_multisensor->Public_measurements(client);
}

void Peripherals_generator::add_multisensor(HAL::Init* hal, JsonDocument& json)
{
    Serial.println(json["HARDWARE_CONFIGURATION"]["SENSOR"].as<String>());
    m_multisensor = new Multisensor(hal->get_bme_sensor(), "greenhouse/sensor/temp");
}

void Peripherals_generator::generate_digital_in_out(HAL::Init* hal, JsonDocument& json)
{
    JsonArray array = json["HARDWARE_CONFIGURATION"]["GPIO_CONTROLLERS"].as<JsonArray>();
    int gpio_count = array.size();
    Serial.println(gpio_count);
    for(int i = 0; i <= gpio_count-1; i++)
    {
        Serial.println(array[i]["ADDRES"].as<String>());
    }
}

} //Peripherals