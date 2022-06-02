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
  Digital_output(HAL::GPIO_controller* controller, PubSubClient& client, int pin, String topic, Scheduler& scheduler);
  void set_value(uint8_t value) override;
  String get_topic();

  private:
  void turn_off();

  HAL::GPIO_controller* m_controller;
  Logger* m_logger;
  Scheduler& m_scheduler;  

  String m_topic;
  uint8_t m_pin;
};

} // namespace Peripherals