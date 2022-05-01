#include "Dht_sensor.h"

namespace HAL
{

Dht_sensor::Dht_sensor()
: m_logger(Logger("DHT_sensor"))
, m_sensor(DHT(Config::dht_pin, DHT22))
{
  m_sensor.begin();
}

float Dht_sensor::get_temp()
{
  return m_sensor.readTemperature();
}

float Dht_sensor::get_hum()
{
  return m_sensor.readHumidity();
}

} // namespace HAL