/**
 * @file Config.h
 * @brief Main configuration file
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @date 06-2022
 */
#pragma once

#include <Arduino.h>
#include <stdint.h>

namespace Config
{

const uint16_t max_json_size = 2048; ///< max json lenght(chars count)

const uint32_t serial_baudrate = 115200; ///< serial baudrate

const uint8_t screen_address = 0x3C; ///< OLED screen I2C address
const uint8_t screen_width = 128; ///< OLED width
const uint8_t screen_height = 64; ///< OLED height

const uint8_t memory_adress = 0x50; ///< EEPROM I2C address

const uint16_t mqtt_port = 1883; ///< MQTT using port
const uint32_t mqtt_publishing_interval = 60000;

static const char* time_server = "pool.ntp.org"; ///< NTP server address
const int32_t time_zone = 7200; ///< UTC offset in seconds
const uint16_t time_synchronization_timeout = 30000; ///< max time for synchronization with ntp

const uint8_t min_adress_gpio_controllers = 32; ///< MCP23017 minimal I2C address
const uint8_t max_adress_gpio_controllers = 39; ///< MCP23017 maximum I2C address

const uint8_t min_adress_analog_controllers = 71; ///< PCF8591 minimal I2C address
const uint8_t max_adress_analog_controllers = 79; ///< PCF8591 maximum I2C address

static const char* m_json_file_name = "config.json"; ///< json file name to read configuration from SD

const String sw_version = "98a901f"; ///< actual software version

const uint32_t max_log_file_size = 2048; // max log file size in //TODO: unit?

} // namespace Config