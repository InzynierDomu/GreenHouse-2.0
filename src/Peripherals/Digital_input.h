/**
 * @file Digital_input.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Digital input handling
 * @date 2022-06
 */

#pragma once

#include "HAL/GPIO_controller.h"
#include "Logger.h"
#include "Peripheral_input.h"

class Logger;

namespace Peripherals
{

class Digital_input : public Peripheral_input
{
  public:
  Digital_input(HAL::GPIO_controller* controller, const uint8_t pin, const String topic);
  void publish(PubSubClient& client) override;

  private:
  HAL::GPIO_controller* m_controller;
  Logger m_logger;

  const String m_topic; ///< mqtt topic to publishing
  const uint8_t m_pin; ///< pin number on expander
};

} // namespace Peripherals