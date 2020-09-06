#include "Init.h"

namespace HAL{

Init::Init()
{
  pinMode(Pins::m_keyboard_int, INPUT_PULLUP);
  m_keyboard = new Keyboard(Config::m_keyboard_pcf_adress);
  
}

void Init::set_keyoboard_buttons(bool *is_pressed, Keyboard_button *button)
{
    
}

} //namespace HAL