/**
 * @file Analog_controller.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Analog output expander
 * @date 2022-06
 */

#include "Analog_controller.h"

#include "Config.h"
#include "Real_clock.h"

namespace HAL
{

/**
 * @brief Construct a new Analog_controller::Analog_controller object
 * @param address: I2C address
 */
Analog_controller::Analog_controller(const uint16_t address)
: m_logger(Logger("Analog_controller", Real_clock::get_instance()->get_time_callback()))
, m_address(address)
, m_expander(PCF8591(address))
{
  m_expander.begin();
}

/**
 * @brief get I2C address expander
 * @return int expander address
 */
uint16_t Analog_controller::get_address() const
{
  return m_address;
}

/**
 * @brief get analog measurment from pin on expander
 * @param pin: pin to read measurment
 * @return uint16_t value of measurment
 */
uint16_t Analog_controller::get_value(const uint8_t pin)
{
  auto value = m_expander.analogRead(pin);
  return value;
}

} // namespace HAL