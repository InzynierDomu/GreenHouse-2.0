#include <Arduino.h>

#ifndef HAL_CONFIG
#define HAL_CONFIG

namespace HAL{
namespace Config{

const byte m_screen_adress = 0x3C;    
const int m_screen_width = 128;
const int m_screen_height = 64; 

const byte m_keyboard_pcf_adress = 0x20;

const int m_memory_adress = 0x50;

const int m_mqtt_port = 1883;

// const char *m_json_file_name = "datalog.json";

} //namespace Config
} //namespace HAL

#endif //HAL_CONFIG