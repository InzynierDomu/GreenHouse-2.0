/**
 * @file Multisensor.cpp
 * @brief GreenHouse 2.0 - Peripheral for BME280
 * @author Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */

#include "Multisensor.h"

namespace Peripherals
{

Multisensor::Multisensor(HAL::Bme_sensor* bme_sensor, char* topic, int pin)
: m_bme_sensor(bme_sensor)
{
  m_topic = topic;
  m_pin = pin;
}

void Multisensor::publish(PubSubClient& client)
{
  char buf[10];
  float measure = m_bme_sensor->get_bme_temp();
  sprintf(buf, "%f", measure);
  String topic = m_topic + "/temp";
  client.publish(topic.c_str(), buf);
  measure = m_bme_sensor->get_bme_hum();
  sprintf(buf, "%f", measure);
  topic = m_topic + "/hum";
  client.publish(topic.c_str(), buf);
}

} // namespace Peripherals
