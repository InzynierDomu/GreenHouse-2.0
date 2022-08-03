/**
 * @file Multisensor.h
 * @brief air temperature and humidity handling
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @date 01-2021
 */
#pragma once

#include "HAL/Dht_sensor.h"
#include "Logger.h"
#include "Peripheral_input.h"

#include <PubSubClient.h>

namespace Peripherals
{
class Multisensor : public Peripheral_input
{
  public:
  Multisensor(HAL::Dht_sensor* dht_sensor, const char* topic);
  void publish(PubSubClient& client) override;

  private:
  HAL::Dht_sensor* m_dht_sensor; ///< temperature and humidity sensor
  Logger m_logger; ///< logger

  String m_topic; ///< mqtt topic
};

} // namespace Peripherals