/**
 * @file Digital_output.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Digital output handling
 * @date 2022-06
 */

#pragma once

#include "HAL/GPIO_controller.h"
#include "Logger.h"
#include "Peripheral_output.h"
#include "Scheduler.h"

#include <PubSubClient.h>

class Logger;

namespace Peripherals
{

class Digital_output : public Peripheral_output
{
  public:
  Digital_output(HAL::GPIO_controller* controller, PubSubClient& client, const uint8_t pin, const String topic, Scheduler& scheduler);
  void set_value(const uint8_t value) override;
  String get_topic() const override;

  private:
  void turn_off();

  HAL::GPIO_controller* m_controller;
  Logger* m_logger;
  Scheduler& m_scheduler;

  const String m_topic; ///< mqtt topic to subscribe
  const uint8_t m_pin; ///< pin number on expander
};

} // namespace Peripherals