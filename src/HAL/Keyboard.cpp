#include "Keyboard.h"

#include "Logger.h"
#include "Pin_config.h"

namespace HAL{

Keyboard* keyboard;
static void ICACHE_RAM_ATTR readpcf();

Keyboard::Keyboard(uint8_t adress)
{
  m_logger = new Logger("Keyboard");
  m_expander = new PCF8574(adress);
  m_expander->begin();

  pinMode(Pins::m_keyboard_int, INPUT_PULLUP);
  keyboard = this;
  attachInterrupt(digitalPinToInterrupt(Pins::m_keyboard_int), readpcf, FALLING);
}

Keyboard::~Keyboard()
{
    delete m_expander;
}

void Keyboard::keyboard_action()
{
  byte state = m_expander->read8();
  if(state != 0xFF)
  {
    byte button = ~state;  
    button = button & 0x7F;
    switch (button)
    {
      case m_button_down:
        m_logger->log("down");
        break;
      case m_button_right:
        m_logger->log("right");
        break;
      case m_button_left:
        m_logger->log("left");
        break;
      case m_button_up:
        m_logger->log("up");
        break;
    }      
  }    
}

static void ICACHE_RAM_ATTR readpcf()
{
  keyboard->m_keyboatd_button_presed = true;
}

}