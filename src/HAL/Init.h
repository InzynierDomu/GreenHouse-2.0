#include "Config.h"
#include "Pin_config.h"
#include "Keyboard.h"
#include "Screen.h"
#include "GPIO_controller.h"
#include "../Keyboard_buttons.h"

namespace HAL{

class Init
{
public:
    Init();
    void set_keyoboard_buttons(bool *is_pressed, Keyboard_button *button);

private:
    Screen *m_screen;
    Keyboard *m_keyboard; 
    GPIO_controller *m_gpio_controller;
};

} //namespace HAL