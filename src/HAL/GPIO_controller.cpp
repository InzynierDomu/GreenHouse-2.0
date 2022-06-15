/**
 * @file GPIO_controller.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief GPIO expander
 * @date 2022-06
 */

#include "GPIO_controller.h"

#include "Config.h"

namespace HAL
{

/**
 * @brief Construct a new gpio controller::gpio controller object
 * @param adress: I2C address
 */
GPIO_controller::GPIO_controller(const uint16_t adress)
: m_adress(adress)
, m_exspander(Adafruit_MCP23X17())
{
  m_exspander.begin_I2C(adress, &Wire);
}

/**
 * @brief set pin input or output
 * @param type: INPUT or OUTPUT
 * @param pin: pin to set
 */
void GPIO_controller::set_in_out(const uint8_t type, const uint8_t pin)
{
  m_exspander.pinMode(pin, type);
}

/**
 * @brief get GPIO vaule
 * @param pin: GPIO number 
 * @return uint8_t readed value 
 */
uint8_t GPIO_controller::get_state(const uint8_t pin)
{
  return m_exspander.digitalRead(pin);
}

/**
 * @brief turn on pin (reverse logic)
 * @param pin: pin to turn on
 */
void GPIO_controller::turn_on_pin(const uint8_t pin)
{
  m_exspander.digitalWrite(pin, LOW);
}

/**
 * @brief turn off pin (reverse logic)
 * @param pin: pin to turn off
 */
void GPIO_controller::turn_off_pin(const uint8_t pin)
{
  m_exspander.digitalWrite(pin, HIGH);
}

/**
 * @brief get I2C address
 * @return uint16_t expander address
 */
uint16_t GPIO_controller::get_address() const
{
  return m_adress;
}

} // namespace HAL