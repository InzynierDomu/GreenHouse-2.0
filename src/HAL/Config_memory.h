#pragma once

#include "Logger.h"
#include "Utilis/Checksum.h"

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

  private:
  void write_EEPROM(unsigned int eeaddress, char data);
  char read_EEPROM(unsigned int eeaddress);

  Logger m_logger;
};

} // namespace HAL