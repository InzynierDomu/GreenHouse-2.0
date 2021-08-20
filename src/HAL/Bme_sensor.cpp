#include "Bme_sensor.h"

namespace HAL
{

Bme_sensor::Bme_sensor():
m_logger(Logger("Bme_sensor"))
{
  if(m_bme_sensor.begin(BME280_ADDRESS_ALTERNATE))
  {
    m_logger.log("BME sensor found on alt address"); 
  }
  else if(m_bme_sensor.begin(BME280_ADDRESS))
  {
    m_logger.log("BME sensor found");
  }
  else
  {
    m_logger.log("BME not found", Log_type::warning);
  }
}

float Bme_sensor::get_bme_temp()
{
  return m_bme_sensor.readTemperature();
}

float Bme_sensor::get_bme_hum()
{
  return m_bme_sensor.readHumidity();
}

float Bme_sensor::get_bme_pres()
{
  return m_bme_sensor.readPressure();
}

} //namespace HAL