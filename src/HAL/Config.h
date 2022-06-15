#pragma once

#include <stdint.h>

namespace HAL
{
namespace Config
{

const int max_json_size = 2048;

const uint8_t screen_adress = 0x3C;
const int screen_width = 128;
const int screen_height = 64;

const int memory_adress = 0x50;

const int mqtt_port = 1883;

static const char* time_server = "pool.ntp.org";
const int time_zone = 7200;
const int time_synchronization_timeout = 30000;

const int min_adress_gpio_controllers = 32;
const int max_adress_gpio_controllers = 39;

const int min_adress_analog_controllers = 71;
const int max_adress_analog_controllers = 79;

// const char *m_json_file_name = "datalog.json";

} // namespace Config
} // namespace HAL