/**
 * @file Peripherals_generator.cpp
 * @brief GreenHouse 2.0 - Class for genereting peripherals object from json config
 * @author Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/  
 * @date 01-2021
 */

#include "Peripherals_generator.h"

#include "Peripheral.h"
#include "math.h"
#include "Logger.h"
#include "HAL/Config.h"
#include <optional>

namespace Peripherals{

Peripherals_generator::Peripherals_generator(HAL::Init* hal, JsonDocument& json, PubSubClient* client):
m_client(client),
m_logger(Logger("Peripherals generator"))
{
	add_multisensor(hal, json);
	generate_digital_in_out(hal, json);
	generate_analog_in(hal, json);
}

std::optional<Digital_output> Peripherals_generator::get_gpio_output(String topic)
{
	//TODO: generic
	for(auto it = m_gpio_outputs.begin(); it != m_gpio_outputs.end(); it++)
	{
		if(topic.equals(it->get_topic()))
		{
			return *(it);
		}
	}
}

Multisensor* Peripherals_generator::get_multisensor()
{
  return m_multisensor;
}
	
std::vector<Digital_input>* Peripherals_generator::get_gpio_inputs()
{
	return &m_gpio_inputs;
}

std::vector<Analog_input>* Peripherals_generator::get_analog_inputs()
{
	return &m_analog_inputs;
}

void Peripherals_generator::add_multisensor(HAL::Init* hal, JsonDocument& json)
{
	Serial.println(json["HARDWARE_CONFIGURATION"]["SENSOR"].as<String>());
	m_multisensor = new Multisensor(hal->get_bme_sensor(), "greenhouse/sensor");
}

void Peripherals_generator::generate_digital_in_out(HAL::Init* hal, JsonDocument& json)
{
	JsonArray array = json["HARDWARE_CONFIGURATION"]["GPIO_CONTROLLERS"].as<JsonArray>();
	const int gpio_count = array.size();
	for(int i = 0; i < gpio_count; i++)
	{
		const String adress = array[i]["ADDRES"].as<String>(); 
		const int hw_adress = HAL::Config::min_adress_gpio_controllers + convert_bin_to_dec(adress);
		auto gpio_controller = hal->get_GPIO_controller(hw_adress);
		if(gpio_controller != nullptr)
		{
			JsonArray pins = json["HARDWARE_CONFIGURATION"]["GPIO_CONTROLLERS"][i]["GPIOS"].as<JsonArray>();
			for(int pin = 0; pin < pins.size(); pin++)
			{
				String pin_type = pins[pin]["TYPE"].as<String>();
				if(!pin_type.compareTo("IN"))
				{
					gpio_controller->set_in_out(INPUT, pin);
					m_gpio_inputs.push_back(Digital_input(*gpio_controller, pin, pins[pin]["TOPIC"].as<String>()));
				}
				else if(!pin_type.compareTo("OUT"))
				{
					gpio_controller->set_in_out(OUTPUT, pin);
					m_gpio_outputs.push_back(Digital_output(*gpio_controller, m_client, pin, pins[pin]["TOPIC"].as<String>()));
				}
			}
		}
	}
}

void Peripherals_generator::generate_analog_in(HAL::Init* hal, JsonDocument& json)
{
	JsonArray array = json["HARDWARE_CONFIGURATION"]["ANALOG_CONTROLLERS"].as<JsonArray>();
	const int analog_count = array.size();
	for(int i = 0; i < analog_count; i++)
	{
		const String adress = array[i]["ADDRES"].as<String>(); 
		const int hw_adress = HAL::Config::min_adress_analog_controllers + convert_bin_to_dec(adress);
		auto analog_controller = hal->get_analog_controller(hw_adress);
		if(analog_controller != nullptr)
		{
			JsonArray pins = json["HARDWARE_CONFIGURATION"]["ANALOG_CONTROLLERS"][i]["INPUTS"].as<JsonArray>();
			for(int pin = 0; pin < pins.size(); pin++)
			{				
				m_analog_inputs.push_back(Analog_input(*analog_controller, pin, pins[pin]["TOPIC"].as<String>()));
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