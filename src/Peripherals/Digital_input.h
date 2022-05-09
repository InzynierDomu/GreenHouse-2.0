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
  Digital_input(HAL::GPIO_controller& controller, int pin, String topic);
  void publish(PubSubClient& client) override;

  private:
  HAL::GPIO_controller& m_controller;
  Logger m_logger;
};

} // namespace Peripherals