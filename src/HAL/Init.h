#ifndef HAL_INIT
#define HAL_INIT

#include "Config.h"
#include "Pin_config.h"
#include "Logger.h"
#include "../Keyboard_buttons.h"

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <vector>
#include <optional>

class Supervisor;

namespace HAL{

class Screen;
class Bme_sensor;
class Keyboard;
class GPIO_controller;
class Analog_controller;
class Wifi;
class SD_reader;
class Config_memory;

class Init
{
public:
    Init(Supervisor& supervisor);
    void initNetwork(JsonDocument& json);
    Bme_sensor* get_bme_sensor();
    GPIO_controller* get_GPIO_controller(int adress);
    Analog_controller* get_analog_controller(int adress);
    PubSubClient* get_wifi_mqtt_client();
    void wifi_mqtt_reconnect();
    void set_mqtt_callback(std::function<void(const char*, byte*, unsigned int)> callback);
    void mqtt_loop();
    void deserializeConfigJson(JsonDocument& json);

private:
    Logger m_logger;
    Supervisor& m_supervisor;
    const Screen* m_screen;
    const Keyboard* m_keyboard; 
    SD_reader* m_sd_reader;
    std::vector<GPIO_controller> m_gpio_controllers;
    std::vector<Analog_controller> m_analog_controllers;
    Bme_sensor* m_bme_sensor;
    Wifi *m_wifi;
    Config_memory* m_config_memory;

    std::vector<int> m_i2c_adress;

    void scan_i2c();
    bool check_main_i2c_peripherals();
    void generate_expander_controllers();
    void synchronize_with_ntp();
    void check_json_file();
};

} //namespace HAL

#endif //HAL_INIT