#pragma once

#include "Logger.h"
#include "Config.h"
#include "DHT.h"

namespace HAL
{

class Dht_sensor
{
  public:
  Dht_sensor();
  float get_temp();
  float get_hum();

  private:
  Logger m_logger;
  DHT m_sensor;
};

} // namespace HAL