#include "Init.h"
#include "Bme_sensor.h"
#include "Keyboard.h"
#include "Screen.h"
#include "Real_clock.h"
#include "Config_memory.h"
#include "SD_reader.h"
#include "GPIO_controller.h"
#include "Analog_controller.h"
#include "Wifi.h"
#include "Supervisor.h"

namespace HAL{

Init::Init(Supervisor& supervisor):
m_logger(Logger("HAL")),
m_supervisor(supervisor)
{
  scan_i2c();
  if(!check_main_i2c_peripherals())
  {
    m_logger.log("Main peripherals not found", Log_type::error);
    m_supervisor.error();
  }
  else
  {
  m_keyboard = new Keyboard(Config::keyboard_pcf_adress);
  m_screen = new Screen();  
  m_bme_sensor = new Bme_sensor();
  m_sd_reader = new SD_reader();
  m_config_memory = new Config_memory();

  generate_expander_controllers();

  if(m_sd_reader->is_card_available())
  {
    String json_file = m_sd_reader->get_json_file();
    if(!json_file.equals(m_config_memory->get_raw_file()))
    {
      m_config_memory->save_json(json_file );
      m_logger.log("New json saving");
    }
    m_logger.log(m_config_memory->get_json());
  }
  }
}

void Init::initNetwork(JsonDocument& json)
{
  m_wifi = new Wifi(json["SSID"], json["PASS"], json["MQTT_SERVER"]);
  synchronize_with_ntp();
}

Bme_sensor* Init::get_bme_sensor()
{
  return m_bme_sensor;
}

GPIO_controller* Init::get_GPIO_controller(int adress)
{
  for(auto it = m_gpio_controllers.begin(); it != m_gpio_controllers.end(); ++it)
  {
    if(it->get_adress() == adress)
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
  for(auto it = m_analog_controllers.begin(); it != m_analog_controllers.end(); ++it)
  {
    if(it->get_adress() == adress)
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

PubSubClient* Init::get_wifi_mqtt_client()
{
  return m_wifi->get_mqtt_client();
}

void Init::wifi_mqtt_reconnect()
{
  //todo: fromconfig
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
  String deserialization_state = deserializeJson(json, m_config_memory->get_json()).c_str();
  if(!deserialization_state.compareTo("Ok"))
  {
    m_logger.log("Deserialization Ok");
  }
  else
  {
    m_logger.log("Deserialization " + deserialization_state, Log_type::warning);
  }
}

void Init::scan_i2c()
{
  Wire.begin();
  for(int address = 1; address < 127; address++ )
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
  for(auto it = m_i2c_adress.begin(); it != m_i2c_adress.end(); ++it)
  {
    if(*it == Config::memory_adress)
    {
      return true;
    }
  }
  return false;
}

void Init::generate_expander_controllers()
{
  for(auto it = m_i2c_adress.begin(); it != m_i2c_adress.end(); ++it)
  {
    if(*it > Config::min_adress_gpio_controllers && *it <= Config::max_adress_gpio_controllers)
    {
      GPIO_controller *gpio_controller = new GPIO_controller(*it);
      m_gpio_controllers.push_back(*gpio_controller);
    }
    else if(*it > Config::min_adress_analog_controllers && *it <= Config::max_adress_analog_controllers)
    {
      Analog_controller *analog_controller = new Analog_controller(*it);
      m_analog_controllers.push_back(*analog_controller);
    }
  }
}

void Init::synchronize_with_ntp()
{
  time_t now = time(nullptr);

  configTime(Config::time_zone, 0, "pool.ntp.org"); //TODO: move to config
  static long last_loop_time = 0;
  long loop_time = millis();
  do
  {
    last_loop_time = millis();
    now = time(nullptr);
    delay(500);
    m_logger.log("*");
  }while((now < 1546300800) && !((last_loop_time - loop_time) > Config::time_synchronization_timeout));
  m_logger.log(String(now));
  auto clock = Real_clock::get_instance();
  clock->adjust(now);
}

void Init::check_json_file()
{

}

} //namespace HAL