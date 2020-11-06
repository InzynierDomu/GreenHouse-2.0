#include "Bme_sensor.h"

namespace HAL
{

Bme_sensor::Bme_sensor()
{
    m_bme_sensor.begin(BME280_ADDRESS_ALTERNATE);
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