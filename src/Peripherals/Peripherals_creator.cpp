/**
 * @file Peripherals_creator.cpp
 * @brief GreenHouse 2.0 - Class for genereting peripherals object from json config
 * @author Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */
#include "Peripherals_creator.h"

#include "Config.h"
#include "HAL/Real_clock.h"
#include "Logger.h"
#include "math.h"

#include <optional>

namespace Peripherals
{

/**
 * @brief Construct a new Peripherals_creator::Peripherals_creator object
 * @param peripherals: peripherals model to fill
 * @param hal: hardware layer
 * @param json: configuration
 * @param client: mqtt client
 * @param scheduler: scheduler
 */
Peripherals_creator::Peripherals_creator(Peripherals* peripherals, HAL::Init* hal, JsonDocument& json, PubSubClient& client,
                                         Scheduler& scheduler)
: m_client(client)
, m_logger(Logger("Peripherals creator", HAL::Real_clock::get_instance()->get_time_callback()))
{
  add_multisensor(peripherals, hal, json);
  generate_digital_in_out(peripherals, hal, json, scheduler);
  generate_analog_in(peripherals, hal, json);
}

void Peripherals_creator::add_multisensor(Peripherals* peripherals, HAL::Init* hal, JsonDocument& json)
{
  auto topic = json["CONFIGURATION"]["HARDWARE_CONFIGURATION"]["SENSOR"].as<String>();
  peripherals->m_inputs.push_back(new Multisensor(hal->get_dht_sensor(), topic.c_str()));
}

void Peripherals_creator::generate_digital_in_out(Peripherals* peripherals, HAL::Init* hal, JsonDocument& json, Scheduler& scheduler)
{
  JsonArray array = json["CONFIGURATION"]["HARDWARE_CONFIGURATION"]["GPIO_CONTROLLERS"].as<JsonArray>();
  const int gpio_controllers_count = array.size();
  for (int i = 0; i < gpio_controllers_count; i++)
  {
    const String adress = array[i]["ADDRES"].as<String>();
    const int hw_adress = Config::min_adress_gpio_controllers + convert_bin_to_dec(adress);
    auto gpio_controller = hal->get_GPIO_controller(hw_adress);
    if (gpio_controller != nullptr)
    {
      JsonArray pins = json["CONFIGURATION"]["HARDWARE_CONFIGURATION"]["GPIO_CONTROLLERS"][i]["GPIOS"].as<JsonArray>();
      for (uint8_t pin = 0; pin < static_cast<uint8_t>(pins.size()); pin++)
      {
        String pin_type = pins[pin]["TYPE"].as<String>();
        if (!pin_type.compareTo("IN"))
        {
          gpio_controller->set_in_out(INPUT, pin);
          peripherals->m_inputs.push_back(new Digital_input(gpio_controller, pin, pins[pin]["TOPIC"].as<String>()));
        }
        else if (!pin_type.compareTo("OUT"))
        {
          gpio_controller->set_in_out(OUTPUT, pin);
          peripherals->m_outputs.push_back(new Digital_output(gpio_controller, m_client, pin, pins[pin]["TOPIC"].as<String>(), scheduler));
        }
      }
    }
  }
}

void Peripherals_creator::generate_analog_in(Peripherals* peripherals, HAL::Init* hal, JsonDocument& json)
{
  JsonArray array = json["CONFIGURATION"]["HARDWARE_CONFIGURATION"]["ANALOG_CONTROLLERS"].as<JsonArray>();
  const int analog_controllers_count = array.size();
  for (int i = 0; i < analog_controllers_count; i++)
  {
    const String adress = array[i]["ADDRES"].as<String>();
    const int hw_adress = Config::min_adress_analog_controllers + convert_bin_to_dec(adress);
    auto analog_controller = hal->get_analog_controller(hw_adress);
    if (analog_controller != nullptr)
    {
      JsonArray pins = json["CONFIGURATION"]["HARDWARE_CONFIGURATION"]["ANALOG_CONTROLLERS"][i]["INPUTS"].as<JsonArray>();
      for (uint8_t pin = 0; pin < static_cast<uint8_t>(pins.size()); pin++)
      {
        peripherals->m_inputs.push_back(new Analog_input(analog_controller, pin, pins[pin]["TOPIC"].as<String>()));
      }
    }
  }
}

int Peripherals_creator::convert_bin_to_dec(String number)
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

} // namespace Peripherals