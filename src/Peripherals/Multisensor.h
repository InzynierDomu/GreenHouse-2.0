/**
 * @file Multisensor.h
 * @brief GreenHouse 2.0 - Peripheral for BME280
 * @author Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */

#ifndef PERIPHERALS_MULTISENSOR
#define PERIPHERALS_MULTISENSOR

#include "HAL/Dht_sensor.h"
#include "Peripheral.h"

#include <PubSubClient.h>

namespace Peripherals
{

class Multisensor : public Peripheral
{
  public:
  Multisensor(HAL::Dht_sensor* dht_sensor, char* topic, int pin = 0);
  void publish(PubSubClient& client);

  private:
  HAL::Dht_sensor* m_dht_sensor;
};

} // namespace Peripherals

#endif // PERIPHERALS_MULTISENSOR