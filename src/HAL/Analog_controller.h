/**
 * @file Analog_controller.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Analog output expander
 * @date 2022-06
 */

#pragma once

#include "Logger.h"

#include "PCF8591.h"

namespace HAL
{

class Analog_controller
{
  public:
  Analog_controller(const uint16_t address);
  uint16_t get_address() const;
  uint16_t get_value(const uint8_t pin);

  private:
  Logger m_logger; ///< logger
  const uint16_t m_address; ///< I2C address
  PCF8591 m_expander; ///< PCF8591 expander
};

} // namespace HAL