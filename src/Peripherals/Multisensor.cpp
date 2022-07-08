/**
 * @file Multisensor.cpp
 * @brief air temperature and humidity handling
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @date 01-2021
 */
#include "Multisensor.h"

#include "HAL/Real_clock.h"

namespace Peripherals
{

/**
 * @brief Construct a new Multisensor:: Multisensor object
 * @param dht_sensor: dht sensor
 * @param topic: mqtt topic to publish
 */
Multisensor::Multisensor(HAL::Dht_sensor* dht_sensor, const char* topic)
: m_dht_sensor(dht_sensor)
, m_logger(Logger("Multisensor", HAL::Real_clock::get_instance()->get_time_callback()))
, m_topic(topic)
{}

/**
 * @brief publish measurments
 * @param client: mqtt client
 */
void Multisensor::publish(PubSubClient& client)
{
  char buf[10];
  float measure = m_dht_sensor->get_temp();
  sprintf(buf, "%f", measure);
  String topic = m_topic + "/temp";
  m_logger.log(buf);
  client.publish(topic.c_str(), buf);
  measure = m_dht_sensor->get_hum();
  sprintf(buf, "%f", measure);
  topic = m_topic + "/hum";
  m_logger.log(buf);
  client.publish(topic.c_str(), buf);
}

} // namespace Peripherals
