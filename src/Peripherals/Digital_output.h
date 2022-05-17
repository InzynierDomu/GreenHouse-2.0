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
  Digital_output(HAL::GPIO_controller& controller, PubSubClient& client, int pin, String topic, Scheduler* scheduler); //todo: add reference to scheduler
  void set_value(uint8_t value) override;
  String get_topic();

  private:
  HAL::GPIO_controller& m_controller;
  Scheduler* m_scheduler;
  Logger* m_logger;

  void turn_off();
};

} // namespace Peripherals