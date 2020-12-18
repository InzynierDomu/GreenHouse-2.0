#include "Peripherals_generator.h"

#include "Peripheral.h"
#include "math.h"

namespace Peripherals{

Peripherals_generator::Peripherals_generator(HAL::Init* hal, JsonDocument& json, PubSubClient* client):
m_client(client)
{
    add_multisensor(hal, json);
    generate_digital_in_out(hal, json);
}

void Peripherals_generator::publish()
{
    m_multisensor->Public_measurements(m_client);

    for(auto it = m_digital_inputs.begin(); it != m_digital_inputs.end(); it++)
    {
        (*it).publish(m_client);
    }
}

void Peripherals_generator::add_multisensor(HAL::Init* hal, JsonDocument& json)
{
    // Serial.println(json["HARDWARE_CONFIGURATION"]["SENSOR"].as<String>());
    m_multisensor = new Multisensor(hal->get_bme_sensor(), "greenhouse/sensor");
}

void Peripherals_generator::generate_digital_in_out(HAL::Init* hal, JsonDocument& json)
{
    JsonArray array = json["HARDWARE_CONFIGURATION"]["GPIO_CONTROLLERS"].as<JsonArray>();
    int gpio_count = array.size();
    for(int i = 0; i <= gpio_count-1; i++)
    {
        String adress = array[i]["ADDRES"].as<String>(); 
        int hw_adress = 32 + convert_bin_to_dec(adress);
        auto gpio_controller = hal->get_GPIO_controller(hw_adress);
        if(gpio_controller != nullptr)
        {
            JsonArray pins = json["HARDWARE_CONFIGURATION"]["GPIO_CONTROLLERS"][i]["GPIOS"].as<JsonArray>();
            for(int pin = 0; pin <= pins.size(); pin++)
            {
                String pin_type = pins[pin]["TYPE"].as<String>();
                if(!pin_type.compareTo("IN"))
                {
                    auto digital_input = new Digital_input(gpio_controller, pin, pins[pin]["TOPIC"].as<String>());
                    gpio_controller->set_in_out(INPUT, pin);
                    m_digital_inputs.push_back(*digital_input);
                }
                else if(!pin_type.compareTo("OUT"))
                {
                    auto digital_output = new Digital_output(gpio_controller, m_client, pin, pins[pin]["TOPIC"].as<String>());
                    m_digital_outputs.push_back(*digital_output);
                }                
            }
        }
    }
}

int Peripherals_generator::convert_bin_to_dec(String number)
{
    int retvalue = 0;
    int i = 0;
    int rem;
    int bits = number.toInt();       
    while (bits != 0)
    {
      rem = bits % 10;
      bits /= 10;
      retvalue += rem * pow(2, i);
      ++i;
    }
    
    return retvalue;
}

} //Peripherals