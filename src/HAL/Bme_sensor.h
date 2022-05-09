#pragma once

#include "Logger.h"

#include <Adafruit_BME280.h>

namespace HAL
{

class Bme_sensor
{
  public:
  Bme_sensor();
  float get_temp();
  float get_hum();
  float get_pres();

  private:
  Logger m_logger;
  Adafruit_BME280 m_bme_sensor;
};
} // namespace HAL