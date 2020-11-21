#include "Multisensor.h"

namespace Peripherals
{

Multisensor::Multisensor(HAL::Bme_sensor* bme_sensor, char* topic, int pin):
m_bme_sensor(bme_sensor)
{
    m_topic = topic;
    m_pin = pin;
}

void Multisensor::Public_measurements(PubSubClient* client)
{
    char buf[10];
    float measure = m_bme_sensor->get_bme_temp();
    sprintf(buf, "%f", measure);
    client->publish("greenhouse/sensor/temp", buf);
    measure = m_bme_sensor->get_bme_hum();
    sprintf(buf, "%f", measure);
    client->publish("greenhouse/sensor/hum", buf);
}

} //Peripherals
