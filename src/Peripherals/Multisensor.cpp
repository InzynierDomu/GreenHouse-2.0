/**
 * @file Multisensor.cpp
 * @brief GreenHouse 2.0 - Peripheral for BME280
 * @author Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */

#include "Multisensor.h"

#include "HAL/Real_clock.h"

namespace Peripherals
{

Multisensor::Multisensor(HAL::Dht_sensor* dht_sensor, const char* topic)
: m_dht_sensor(dht_sensor)
, m_logger(Logger("Multisensor", HAL::Real_clock::get_instance()->get_time_callback()))
{
  m_topic = topic;
}

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
