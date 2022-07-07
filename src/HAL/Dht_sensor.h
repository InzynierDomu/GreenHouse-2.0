/**
 * @file Dht_sensor.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief air temperature and humidity sensor
 * @date 07-2022
 */
#pragma once

#include "Pin_config.h"
#include "DHT.h"
#include "Logger.h"

namespace HAL
{

class Dht_sensor
{
  public:
  Dht_sensor();
  float get_temp();
  float get_hum();

  private:
  Logger m_logger;  ///< logger
  DHT m_sensor; ///< DHT 22 handling
};

} // namespace HAL