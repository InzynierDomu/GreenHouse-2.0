/**
 * @file Dht_sensor.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief air temperature and humidity sensor
 * @date 07-2022
 */
#include "Dht_sensor.h"

#include "Pin_config.h"
#include "Real_clock.h"

namespace HAL
{

/**
 * @brief Construct a new Dht_sensor::Dht_sensor object
 */
Dht_sensor::Dht_sensor()
: m_logger(Logger("DHT_sensor", Real_clock::get_instance()->get_time_callback()))
, m_sensor(DHT(Pins::dht_pin, DHT22))
{
  m_sensor.begin();
}

/**
 * @brief get temperature from sensor
 * @return air temperature
 */
float Dht_sensor::get_temp()
{
  return m_sensor.readTemperature();
}

/**
 * @brief get humidity from sensor
 * @return air humidity
 */
float Dht_sensor::get_hum()
{
  return m_sensor.readHumidity();
}

} // namespace HAL