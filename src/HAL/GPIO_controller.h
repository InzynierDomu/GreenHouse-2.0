/**
 * @file GPIO_controller.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief GPIO expander
 * @date 2022-06
 */

#pragma once

#include <Adafruit_MCP23X17.h>
#include <Wire.h>

namespace HAL
{

class GPIO_controller
{
  public:
  GPIO_controller(const uint16_t adress);

  void set_in_out(const uint8_t type, const uint8_t pin);
  uint8_t get_state(const uint8_t pin);
  void turn_on_pin(const uint8_t pin);
  void turn_off_pin(const uint8_t pin);  
  uint16_t get_address() const;

  private:
  const uint16_t m_adress;

  Adafruit_MCP23X17 m_exspander;
};
} // namespace HAL