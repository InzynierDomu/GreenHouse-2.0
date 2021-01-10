#include "Init.h"
#include "Logger.h"
#include "Bme_sensor.h"
#include "Keyboard.h"
#include "Screen.h"
#include "Real_clock.h"
#include "Config_memory.h"
#include "SD_reader.h"
#include "GPIO_controller.h"
#include "Wifi.h"

namespace HAL{

Init::Init(JsonDocument& json)
{
  m_logger = new Logger("HAL");
  scan_i2c();

  m_keyboard = new Keyboard(Config::m_keyboard_pcf_adress);
  m_screen = new Screen();  
  m_bme_sensor = new Bme_sensor();
  m_wifi = new Wifi(json["SSID"], json["PASS"], json["MQTT_SERVER"]);
  m_sd_reader = new SD_reader();
  m_config_memory = new Config_memory();
  m_real_clock = new Real_clock();

  m_logger->log(m_real_clock->get_time());

  generate_gpio_controllers();

  if(m_sd_reader->is_card_available())
  {
    String json_file = m_sd_reader->get_json_file();
    if(!json_file.equals(m_config_memory->get_raw_file()))
    {
      m_config_memory->save_json(json_file );
      m_logger->log("New json saving");
    }
    m_logger->log(m_config_memory->get_json());
  }
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
      m_logger->log("Couldn't find gpio controller", Msg_type::warning);
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
  m_wifi->mqtt_reconnect("greenhouse/pump");
}

void Init::set_mqtt_callback(std::function<void(const char*, byte*, unsigned int)> callback)
{
  m_wifi->set_callback(callback);
}

void Init::mqtt_loop()
{
  m_wifi->loop();
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
      m_logger->log("I2C device found at address " + String(address));
    }
  }
}

void Init::generate_gpio_controllers()
{
    for(auto it = m_i2c_adress.begin(); it != m_i2c_adress.end(); ++it)
    {
      if(*it > min_adress_gpio_controllers && *it <= max_adress_gpio_controllers)
      {
        GPIO_controller *gpio_controller = new GPIO_controller(*it);
        m_gpio_controllers.push_back(*gpio_controller);
      }
    }
}

} //namespace HAL