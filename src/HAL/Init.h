#include "Config.h"
#include "Pin_config.h"
#include "../Keyboard_buttons.h"
#include <Adafruit_BME280.h>

#ifndef HAL_INIT
#define HAL_INIT

namespace HAL{

class Screen;
class Keyboard;
class GPIO_controller;

class Init
{
public:
    Init();
    void set_keyoboard_buttons(bool *is_pressed, Keyboard_button *button);
    
    float get_bme_temp();
    float get_bme_hum();

private:
    const Screen *m_screen;
    const Keyboard *m_keyboard; 
    const GPIO_controller *m_gpio_controller;
    Adafruit_BME280 m_bme_sensor;

    void Bme_init();
};

} //namespace HAL

#endif //HAL_INIT