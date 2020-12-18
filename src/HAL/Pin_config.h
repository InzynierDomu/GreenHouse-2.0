#include <Arduino.h>

#ifndef HAL_PINS
#define HAL_PINS

namespace HAL{
namespace Pins{
    const byte m_keyboard_int = D5;
    const byte m_SD_reader_CS = D8;
} //namespace Pins
} //namespace HAL

#endif //HAL_PINS