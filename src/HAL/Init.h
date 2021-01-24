#ifndef HAL_INIT
#define HAL_INIT

#include "Config.h"
#include "Pin_config.h"
#include "../Keyboard_buttons.h"

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <vector>

class Logger;

namespace HAL{

class Screen;
class Bme_sensor;
class Keyboard;
class GPIO_controller;
class Wifi;
class SD_reader;
class Config_memory;
class Real_clock;

class Init
{
public:
    Init(JsonDocument& json);
    Bme_sensor* get_bme_sensor();
    GPIO_controller* get_GPIO_controller(int adress);
    PubSubClient* get_wifi_mqtt_client();
    void wifi_mqtt_reconnect();
    void set_mqtt_callback(std::function<void(const char*, byte*, unsigned int)> callback);
    void mqtt_loop();

private:
    Logger* m_logger;
    const Screen* m_screen;
    const Keyboard* m_keyboard; 
    SD_reader* m_sd_reader;
    std::vector<GPIO_controller> m_gpio_controllers;
    Bme_sensor* m_bme_sensor;
    Wifi *m_wifi;
    Config_memory* m_config_memory;
    Real_clock* m_real_clock;

    std::vector<int> m_i2c_adress;

    void scan_i2c();
    void generate_gpio_controllers();
};

} //namespace HAL

#endif //HAL_INIT