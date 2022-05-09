#pragma once

#include <Adafruit_MCP23017.h>
#include <Wire.h>

namespace HAL
{

class GPIO_controller
{
  public:
  GPIO_controller(const int adress);

  void set_in_out(const int type, const int pin);
  uint8_t get_state(const int pin);
  void set_state(const int pin, const uint8_t state);
  int get_adress() const;

  private:
  const int m_adress;

  Adafruit_MCP23017 m_exspander;
};
} // namespace HAL