/**
 * @file Pin config.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief pinout configuration
 * @date 2022-06
 */
#pragma once

#include <stdint.h>

namespace HAL
{
namespace Pins
{
#ifdef ESP8266
const uint8_t SD_reader_CS = 15; ///< CS in SPI to SD card
const uint8_t dht_pin = 0; ///< DHT 22 sensor data pin
#elif ESP32
const uint8_t SD_reader_CS = 4; ///< CS in SPI to SD card
const uint8_t dht_pin = 3; ///< DHT 22 sensor data pin
#endif
} // namespace Pins
} // namespace HAL