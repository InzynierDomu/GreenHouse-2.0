/**
 * @file Peripherals_creator.h
 * @brief Genereting peripherals object from json config
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @date 01-2021
 */
#pragma once

#include "Analog_input.h"
#include "Digital_input.h"
#include "Digital_output.h"
#include "HAL/Init.h"
#include "Multisensor.h"
#include "Peripherals.h"
#include "Scheduler.h"

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <optional>
#include <vector>

class Logger;

namespace Peripherals
{

class Peripherals_creator
{
  public:
  Peripherals_creator(Peripherals* peripherals, HAL::Init* hal, JsonDocument& json, PubSubClient& client, Scheduler& scheduler);

  private:
  PubSubClient& m_client; ///< mqtt client
  Logger m_logger; ///< logger

  void add_multisensor(Peripherals* peripherals, HAL::Init* hal, JsonDocument& json);
  void generate_digital_in_out(Peripherals* peripherals, HAL::Init* hal, JsonDocument& json, Scheduler& Scheduler);
  void generate_analog_in(Peripherals* peripherals, HAL::Init* hal, JsonDocument& json);

  int convert_bin_to_dec(String number);
};

} // namespace Peripherals