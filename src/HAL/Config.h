#include <Arduino.h>

#ifndef HAL_CONFIG
#define HAL_CONFIG

namespace HAL{
namespace Config{

const byte m_screen_adress = 0x3C;    
const int m_screen_width = 128;
const int m_screen_height = 64; 

const byte m_keyboard_pcf_adress = 0x20;

const byte m_GPIO_controller_adress = 0x24;

} //namespace Config
} //namespace HAL

#endif //HAL_CONFIG