#include <Arduino.h>

#ifndef HAL_PINS
#define HAL_PINS

namespace HAL{
namespace Pins{
    const byte m_analog = A0;
    const byte m_keyboard_int = D5;
} //namespace Pins
} //namespace HAL

#endif //HAL_PINS