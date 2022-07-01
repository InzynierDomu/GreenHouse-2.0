/**
 * @file Init.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Main HAL run
 * @date 2022-06
 */

#include "Init.h"

#include "Analog_controller.h"
#include "Config_memory.h"
#include "Dht_sensor.h"
#include "GPIO_controller.h"
#include "Real_clock.h"
#include "SD_card.h"
#include "Screen.h"
#include "Supervisor.h"
#include "Utilis/Checksum.h"
#include "Wifi.h"

namespace HAL
{

Init::Init(Supervisor& supervisor)
: m_logger(Logger("HAL", Real_clock::get_instance()->get_time_callback()))
, m_supervisor(supervisor)
{
  m_sd_reader = SD_card::get_instance();
  m_logger.set_saving_callback(m_sd_reader->get_save_log_callback());
  scan_i2c();
  // TODO: if screen
  m_screen = std::make_unique<Screen>();
  if (!check_main_i2c_peripherals())
  {
    m_logger.log("memory not found", Log_type::error);
    m_supervisor.error();
  }
  else
  {
    m_dht_sensor = std::make_unique<Dht_sensor>();
    m_config_memory = new Config_memory();
    generate_expander_controllers();
  }
}

void Init::initNetwork(JsonDocument& json)
{
  Mqtt_config mqtt_config = Mqtt_config(json["CONFIGURATION"]["MQTT_SERVER"],
                                        json["CONFIGURATION"]["MQTT_USER"],
                                        json["CONFIGURATION"]["MQTT_ID"],
                                        json["CONFIGURATION"]["MQTT_PASS"]);
  m_wifi = new Wifi(json["CONFIGURATION"]["SSID"], json["CONFIGURATION"]["PASS"], mqtt_config);
  synchronize_with_ntp();
}

Dht_sensor* Init::get_dht_sensor()
{
  return m_dht_sensor.get();
}

GPIO_controller* Init::get_GPIO_controller(int address)
{
  if (!m_gpio_controllers.empty())
  {
    for (auto it = m_gpio_controllers.begin(); it != m_gpio_controllers.end(); ++it)
    {
      if (it->get_address() == address)
      {
        return &(*it);
      }
      else
      {
        m_logger.log("Couldn't find gpio controller", Log_type::warning);
        return nullptr;
      }
    }
  }
  m_logger.log("Couldn't find gpio controller", Log_type::warning);
  return nullptr;
}

Analog_controller* Init::get_analog_controller(int address)
{
  if (!m_analog_controllers.empty())
  {

    for (auto it = m_analog_controllers.begin(); it != m_analog_controllers.end(); ++it)
    {
      if (it->get_address() == address)
      {
        return &(*it);
      }
      else
      {
        m_logger.log("Couldn't find analog controller", Log_type::warning);
        return nullptr;
      }
    }
  }
  m_logger.log("Couldn't analog controller", Log_type::warning);
  return nullptr;
}

PubSubClient& Init::get_wifi_mqtt_client()
{
  return m_wifi->get_mqtt_client();
}

Screen* Init::get_screen()
{
  return m_screen.get();
}

void Init::wifi_mqtt_reconnect()
{
  // TODO: from config
  m_wifi->mqtt_reconnect("greenhouse/output/#");
}

void Init::set_mqtt_callback(std::function<void(const char*, byte*, unsigned int)> callback)
{
  m_wifi->set_mqtt_callback(callback);
}

void Init::mqtt_loop()
{
  m_wifi->loop();
}

void Init::deserializeConfigJson(JsonDocument& json)
{
  if (m_sd_reader->is_card_available())
  {
    String json_file = m_sd_reader->get_json_file();
    m_config_memory->get_json();
    if (m_sd_reader->get_crc() != m_config_memory->get_crc() && !json_file.isEmpty())
    {
      m_config_memory->save_json(json_file);
      m_logger.log("New json saving");
      m_logger.log("SD json: " + json_file, Log_type::debug);
    }
    else
    {
      m_logger.log("SD and memory config is the same");
    }
    m_logger.log("memory json: " + m_config_memory->get_json(), Log_type::debug);
  }

#ifdef LOCAL_JSON
#include "local_json.h"
  String deserialization_state = deserializeJson(json, local_json).c_str();
#endif
#ifndef LOCAL_JSON
  String deserialization_state = deserializeJson(json, m_config_memory->get_json()).c_str();
#endif

  if (!deserialization_state.compareTo("Ok"))
  {
    m_logger.log("Deserialization Ok");
  }
  else
  {
    m_logger.log("Deserialization " + deserialization_state, Log_type::error);
    m_supervisor.error();
  }
}

void Init::scan_i2c()
{
  Wire.begin();
  for (int address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();
    if (error == 0)
    {
      m_i2c_adress.push_back(address);
      m_logger.log("I2C device found at address " + String(address));
    }
  }
}

bool Init::check_main_i2c_peripherals()
{
  for (auto it = m_i2c_adress.begin(); it != m_i2c_adress.end(); ++it)
  {
    if (*it == Config::memory_adress)
    {
      return true;
    }
  }
  return false;
}

void Init::generate_expander_controllers()
{
  for (auto it = m_i2c_adress.begin(); it != m_i2c_adress.end(); ++it)
  {
    if (*it > Config::min_adress_gpio_controllers && *it <= Config::max_adress_gpio_controllers)
    {
      GPIO_controller* gpio_controller = new GPIO_controller(*it);
      m_gpio_controllers.push_back(*gpio_controller);
    }
    else if (*it > Config::min_adress_analog_controllers && *it <= Config::max_adress_analog_controllers)
    {
      Analog_controller* analog_controller = new Analog_controller(*it);
      m_analog_controllers.push_back(*analog_controller);
    }
  }
}

void Init::synchronize_with_ntp()
{
  time_t now = time(nullptr);

  configTime(Config::time_zone, 0, Config::time_server);
  static long last_loop_time = 0;
  long loop_time = millis();
  do
  {
    last_loop_time = millis();
    now = time(nullptr);
    delay(500);
    m_logger.log("*");
  } while ((now < 1546300800) && !((last_loop_time - loop_time) > Config::time_synchronization_timeout));
  auto clock = Real_clock::get_instance();
  clock->adjust(now);
}

} // namespace HAL