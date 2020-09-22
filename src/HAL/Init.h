#include "Config.h"
#include "Pin_config.h"
#include "../Keyboard_buttons.h"

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

private:
    const Screen *m_screen;
    const Keyboard *m_keyboard; 
    const GPIO_controller *m_gpio_controller;
};

} //namespace HAL

#endif //HAL_INIT