/**
 * @file Config_memory.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief EEPROM handling for JSON configuration
 * @date 2022-06
 */
#pragma once

#include "Logger.h"

#include <Wire.h>
#include <istream>

namespace HAL
{

class Config_memory
{
  public:
  Config_memory();
  void save_json(String& file);
  String get_json();
  uint32_t get_crc() const;

  private:
  void write_EEPROM(unsigned int eeaddress, const byte data);
  byte read_EEPROM(unsigned int eeaddress);

  Logger m_logger; ///< logger
  uint32_t m_crc; ///< last loaded configuration json crc
};

} // namespace HAL