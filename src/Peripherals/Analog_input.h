/**
 * @file Analog_input.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Analog input handling
 * @date 2022-06
 */

#pragma once

#include "HAL/Analog_controller.h"
#include "Peripheral_input.h"

class Logger;

namespace Peripherals
{

class Analog_input : public Peripheral_input
{
  public:
  Analog_input(HAL::Analog_controller* controller, const uint8_t pin, const String& topic);
  void publish(PubSubClient& client) override;

  private:
  HAL::Analog_controller* m_controller;
  Logger m_logger;

  const String& m_topic; ///< mqtt topic to publishing
  const uint8_t m_pin; ///< pin number on expander
};

} // namespace Peripherals