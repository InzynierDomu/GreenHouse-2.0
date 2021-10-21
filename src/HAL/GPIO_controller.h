#ifndef HAL_GPIO_CONTROLLER
#define HAL_GPIO_CONTROLLER

#include <Adafruit_MCP23017.h>
#include <Arduino.h>
#include <Wire.h>

namespace HAL
{

class GPIO_controller
{
  public:
  GPIO_controller(const int adress);

  void set_in_out(const int type, const int pin);
  byte get_state(const int pin);
  void set_state(const int pin, const byte state);
  int get_adress() const;

  private:
  const int m_adress;

  Adafruit_MCP23017 m_exspander;
};
} // namespace HAL

#endif // HAL_GPIO_CONTROLLER