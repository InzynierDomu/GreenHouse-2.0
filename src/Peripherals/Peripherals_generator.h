/**
 * @file Peripherals_generator.h
 * @brief GreenHouse 2.0 - Class for genereting peripherals object from json config
 * @author Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/  
 * @date 01-2021
 */

#ifndef PERIPHERALS_PERIPHERALS_GENERATOR
#define PERIPHERALS_PERIPHERALS_GENERATOR

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <vector>
#include <optional>

#include "Analog_input.h"
#include "Digital_input.h"
#include "Digital_output.h"
#include "Multisensor.h"
#include "HAL/Init.h"

class Logger;

namespace Peripherals{

class Peripherals_generator
{
public:
  Peripherals_generator(HAL::Init* hal, JsonDocument& json, PubSubClient* client);
  std::optional<Digital_output> get_gpio_output(String topic);
  Multisensor* get_multisensor();
  std::vector<Digital_input>* get_gpio_inputs();
  std::vector<Analog_input>* get_analog_inputs();
  void publish();

private:
  std::vector<Digital_output> m_gpio_outputs;
  std::vector<Digital_input> m_gpio_inputs;
  std::vector<Analog_input> m_analog_inputs;
  PubSubClient* m_client;
  Multisensor* m_multisensor;
  Logger m_logger;

  void add_multisensor(HAL::Init* hal, JsonDocument& json);
  void generate_digital_in_out(HAL::Init* hal, JsonDocument& json);
  void generate_analog_in(HAL::Init* hal, JsonDocument& json);

  int convert_bin_to_dec(String number);
};    

} //Peripherals

#endif //PERIPHERALS_PERIPHERALS_GENERATOR