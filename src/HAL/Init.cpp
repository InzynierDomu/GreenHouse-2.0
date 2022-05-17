#include "Init.h"

#include "Analog_controller.h"
#include "Config_memory.h"
#include "Dht_sensor.h"
#include "GPIO_controller.h"
#include "Keyboard.h"
#include "Real_clock.h"
#include "SD_reader.h"
#include "Screen.h"
#include "Supervisor.h"
#include "Wifi.h"


namespace HAL
{

Init::Init(Supervisor& supervisor)
: m_logger(Logger("HAL", Real_clock::get_instance()->get_time_callback()))
, m_supervisor(supervisor)
{
  scan_i2c();
  if (!check_main_i2c_peripherals())
  {
    m_logger.log("Main peripherals not found", Log_type::error);
    m_supervisor.error();
  }
  else
  {
    m_keyboard = new Keyboard(Config::keyboard_pcf_adress);
    m_screen = new Screen();
    m_dht_sensor = new Dht_sensor();
    m_sd_reader = new SD_reader();
    m_config_memory = new Config_memory();
    generate_expander_controllers();

    if (m_sd_reader->is_card_available())
    {
      String json_file = m_sd_reader->get_json_file();
      if (!json_file.equals(m_config_memory->get_json())) // todo: add crc
      {
        m_config_memory->save_json(json_file);
        m_logger.log("New json saving");
        m_logger.log("SD json: " + json_file, Log_type::debug);
      }
      m_logger.log("memory json: " + m_config_memory->get_json(), Log_type::debug);
    }
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
  return m_dht_sensor;
}

GPIO_controller* Init::get_GPIO_controller(int adress)
{
  if (m_gpio_controllers.empty())
  {
    return nullptr;
    m_logger.log("Couldn't find gpio controller", Log_type::warning);
  }
  for (auto it = m_gpio_controllers.begin(); it != m_gpio_controllers.end(); ++it)
  {
    if (it->get_adress() == adress)
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

Analog_controller* Init::get_analog_controller(int adress)
{
  for (auto it = m_analog_controllers.begin(); it != m_analog_controllers.end(); ++it)
  {
    if (it->get_adress() == adress)
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

PubSubClient& Init::get_wifi_mqtt_client()
{
  return m_wifi->get_mqtt_client();
}

void Init::wifi_mqtt_reconnect()
{
  // todo: fromconfig
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
  // todo: check crc
  String deserialization_state;

#ifdef LOCAL_JSON
#include "local_json.h"
  deserialization_state = deserializeJson(json, local_json).c_str();
#endif
#ifndef LOCAL_JSON
  deserialization_state = deserializeJson(json, m_config_memory->get_json()).c_str();
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

  configTime(Config::time_zone, 0, "pool.ntp.org"); // TODO: move to config
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

void Init::check_json_file() {}

} // namespace HAL