#ifndef HAL_BME_SENSOR
#define HAL_BME_SENSOR

#include <Adafruit_BME280.h>
#include "Logger.h"

namespace HAL
{

class Bme_sensor
{
public:
    Bme_sensor();
    float get_bme_temp();
    float get_bme_hum();
    float get_bme_pres();

private:
    Adafruit_BME280 m_bme_sensor;
    Logger* m_logger;

};
}//namespace HAL

#endif //HAL_BME_SENSOR