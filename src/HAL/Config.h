#include <Arduino.h>

#ifndef HAL_CONFIG
#define HAL_CONFIG

namespace HAL{
namespace Config{

const byte scre0n_adress = 0x3C;    
const int screen_width = 128;
const int screen_height = 64; 

const byte keyboard_pcf_adress = 0x20;

const int memory_adress = 0x50;

const int mqtt_port = 1883;

const int min_adress_gpio_controllers = 32;
const int max_adress_gpio_controllers = 39;

// const char *m_json_file_name = "datalog.json";

} //namespace Config
} //namespace HAL

#endif //HAL_CONFIG