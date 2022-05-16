#include "Bme_sensor.h"

#include "Real_clock.h" 

namespace HAL
{

Bme_sensor::Bme_sensor()
: m_logger(Logger("Bme_sensor", Real_clock::get_instance()->get_time_callback()))
{
  if (m_bme_sensor.begin(BME280_ADDRESS_ALTERNATE))
  {
    m_logger.log("BME sensor found on alt address");
  }
  else if (m_bme_sensor.begin(BME280_ADDRESS))
  {
    m_logger.log("BME sensor found");
  }
  else
  {
    m_logger.log("BME not found", Log_type::warning);
  }
}

float Bme_sensor::get_temp()
{
  return m_bme_sensor.readTemperature();
}

float Bme_sensor::get_hum()
{
  return m_bme_sensor.readHumidity();
}

float Bme_sensor::get_pres()
{
  return m_bme_sensor.readPressure();
}

} // namespace HAL