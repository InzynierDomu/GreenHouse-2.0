#include "Bme_sensor.h"

namespace HAL
{

Bme_sensor::Bme_sensor()
{
  if(m_bme_sensor.begin(BME280_ADDRESS_ALTERNATE))
  {
    m_logger = new Logger("BME sensor alt"); 
  }
  else if(m_bme_sensor.begin(BME280_ADDRESS))
  {
    m_logger = new Logger("BME sensor");
  }
  else
  {
    m_logger = new Logger("BME not found");
  }
}

float Bme_sensor::get_bme_temp()
{
  float temp = m_bme_sensor.readTemperature();
  m_logger->log(String(temp));
  return temp;
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