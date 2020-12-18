#include <Wire.h>
#include <PCF8574.h>

#ifndef HAL_KEYBOARD
#define HAL_KEYBOARD

class Logger;

namespace HAL{

class Keyboard{
public:
    Keyboard(uint8_t adress);
    ~Keyboard();
    void keyboard_action();

    bool volatile m_keyboatd_button_presed;

private:
    Logger* m_logger;
    PCF8574* m_expander;
 
    static const byte m_led = 7;
    static const byte m_button_down = 4;
    static const byte m_button_right = 8;
    static const byte m_button_left = 2;
    static const byte m_button_up = 1;
};
};

#endif //HAL_KEYBOARD