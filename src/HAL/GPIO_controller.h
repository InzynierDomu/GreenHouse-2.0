#pragma once

#include <Adafruit_MCP23X17.h>
#include <Wire.h>

namespace HAL
{

class GPIO_controller
{
  public:
  GPIO_controller(const int adress);

  void set_in_out(const int type, const int pin);
  uint8_t get_state(const int pin);
  void turn_on_pin(const int pin);
  void turn_off_pin(const int pin);  
  int get_adress() const;

  private:
  const int m_adress;

  Adafruit_MCP23X17 m_exspander;
};
} // namespace HAL