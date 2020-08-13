#include "Keyboard.h"

namespace HAL{

Keyboard::Keyboard(uint8_t adress)
{
  
  // Wire.begin();
  // Wire.beginTransmission(0x20);
  // byte error = Wire.endTransmission();
  // if (error == 0)
  // {
  //   Serial.println("pcf ok!");
  // }
  // else
  // {
  //   Serial.println("pcf not ok ):");
  // }


    m_expander = new PCF8574(adress);
    m_expander->begin();
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
        Serial.println("down");
        m_expander->write(7, 1);
        break;
      case m_button_right:
        Serial.println("right");
        m_expander->write(7, 0);
        break;
      case m_button_left:
        Serial.println("left");
        m_expander->write(7, 0);
        break;
      case m_button_up:
        Serial.println("up");
        m_expander->write(7, 1);
        break;
      }      
    }    
}

}