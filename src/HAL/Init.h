#include <vector>

#include "Config.h"
#include "Pin_config.h"
#include "../Keyboard_buttons.h"

#ifndef HAL_INIT
#define HAL_INIT

namespace HAL{

class Screen;
class Bme_sensor;
class Keyboard;
class GPIO_controller;

class Init
{
public:
    Init();
    Bme_sensor* get_bme_sensor();
    GPIO_controller* get_GPIO_controller(int adress);
    // void set_keyoboard_buttons(bool *is_pressed, Keyboard_button *button);

private:
    const Screen *m_screen;
    const Keyboard *m_keyboard; 
    std::vector<GPIO_controller> m_gpio_controllers;
    Bme_sensor *m_bme_sensor;

    std::vector<int> m_i2c_adress;

    const int min_adress_gpio_controllers = 32;
    const int max_adress_gpio_controllers = 39;

    void scan_i2c();
    void generate_gpio_controllers();
};

} //namespace HAL

#endif //HAL_INIT