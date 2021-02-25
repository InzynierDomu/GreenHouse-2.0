/**
 * @file Multisensor.h
 * @brief GreenHouse 2.0 - Peripheral for BME280
 * @author Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/  
 * @date 01-2021
 */

#ifndef PERIPHERALS_MULTISENSOR
#define PERIPHERALS_MULTISENSOR

#include <PubSubClient.h>

#include "Peripheral.h"
#include "HAL/Bme_sensor.h"

namespace Peripherals
{

class Multisensor : public Peripheral
{    
public:
    Multisensor(HAL::Bme_sensor* bme_sensor, char* topic, int pin = 0);
    void publish(PubSubClient* client);

private:
    HAL::Bme_sensor* m_bme_sensor;
};

} //Peripherals

#endif //PERIPHERALS_MULTISENSOR