/**
 * @file Init.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Main HAL run
 * @date 2022-06
 */
#pragma once

#include "Config.h"
#include "Logger.h"
#include "Pin_config.h"

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <memory>
#include <optional>
#include <vector>

class Supervisor;

namespace HAL
{

class Screen;
class Dht_sensor;
class GPIO_controller;
class Analog_controller;
class Network;
class SD_card;
class Config_memory;

class Init
{
  public:
  Init(Supervisor& supervisor);
  void initNetwork(JsonDocument& json);
  Dht_sensor* get_dht_sensor();
  GPIO_controller* get_GPIO_controller(int address);
  Analog_controller* get_analog_controller(int address);
  PubSubClient& get_mqtt_client();
  Screen* get_screen();
  void wifi_mqtt_reconnect();
  void set_mqtt_callback(std::function<void(const char*, byte*, unsigned int)> callback);
  void mqtt_loop();
  void deserialize_config_json(JsonDocument& json);

  private:
  Logger m_logger;
  Supervisor& m_supervisor;
  std::unique_ptr<Screen> m_screen;
  SD_card* m_sd_reader;
  std::vector<GPIO_controller> m_gpio_controllers;
  std::vector<Analog_controller> m_analog_controllers;
  std::unique_ptr<Dht_sensor> m_dht_sensor;
  Network* m_network;
  Config_memory* m_config_memory;

  std::vector<int> m_i2c_adress;

  void scan_i2c();
  bool check_main_i2c_peripherals();
  void generate_expander_controllers();
  void synchronize_with_ntp();
};

} // namespace HAL