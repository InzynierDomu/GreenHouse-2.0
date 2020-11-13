#include "Peripherals_generator.h"
#include "Peripheral.h"
#include "math.h"

namespace Peripherals{

Peripherals_generator::Peripherals_generator(HAL::Init* hal, JsonDocument& json)
{
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
    m_multisensor = new Multisensor(hal->get_bme_sensor(), "greenhouse/sensor");
}

void Peripherals_generator::generate_digital_in_out(HAL::Init* hal, JsonDocument& json)
{
    JsonArray array = json["HARDWARE_CONFIGURATION"]["GPIO_CONTROLLERS"].as<JsonArray>();
    int gpio_count = array.size();
    Serial.println(gpio_count);
    for(int i = 0; i <= gpio_count-1; i++)
    {
        String adress = array[i]["ADDRES"].as<String>(); 
        int hw_adress = 32 + convert_bin_to_dec(adress);
        auto gpio_controller = hal->get_GPIO_controller(hw_adress);
        if(gpio_controller != nullptr)
        {
            JsonArray pins = json["HARDWARE_CONFIGURATION"]["GPIO_CONTROLLERS"][i]["GPIOS"].as<JsonArray>();
            for(int j = 0; j <= pins.size(); j++)
            {
                String pin_type = pins[j]["TYPE"].as<String>();
                Serial.println(pin_type);
                if(!pin_type.compareTo("IN"))
                {
                    char* topic;
                    pins[j]["TOPIC"].as<String>().toCharArray(topic, 20);
                    auto digital_input = new Digital_input(gpio_controller, j, topic);
                    m_digital_inputs.push_back(digital_input);
                }
                else if(!pin_type.compareTo("OUT"))
                {
                    char* topic;
                    pins[j]["TOPIC"].as<String>().toCharArray(topic, 20);
                    auto digital_output = new Digital_output(gpio_controller, j, topic);
                    m_digital_outputs.push_back(digital_output);
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