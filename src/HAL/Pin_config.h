#pragma once

#include <stdint.h>

namespace HAL
{
namespace Pins
{
#ifdef ESP8266
const uint8_t m_SD_reader_CS = 8;
const uint8_t dht_pin = 3;
#elif ESP32
const uint8_t m_keyboard_int = 5;
const uint8_t m_SD_reader_CS = 4;
const uint8_t dht_pin = 3;
#endif
} // namespace Pins
} // namespace HAL