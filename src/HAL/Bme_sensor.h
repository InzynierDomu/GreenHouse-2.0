#ifndef HAL_BME_SENSOR
#define HAL_BME_SENSOR

#include "Logger.h"

#include <Adafruit_BME280.h>

namespace HAL
{

class Bme_sensor
{
  public:
  Bme_sensor();
  float get_bme_temp();
  float get_bme_hum();
  float get_bme_pres();

  private:
  Logger m_logger;
  Adafruit_BME280 m_bme_sensor;
};
} // namespace HAL

#endif // HAL_BME_SENSOR