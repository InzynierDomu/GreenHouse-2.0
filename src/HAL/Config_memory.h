#ifndef HAL_CONFIGMEMORY_CONTROLLER
#define HAL_CONFIGMEMORY_CONTROLLER

#include <Wire.h>
#include "Logger.h"
#include "Utilis/Checksum.h"

namespace HAL
{

class Config_memory
{
public:
  Config_memory();
  void save_json(String file);
  String get_json();
  String get_raw_file();
  int get_json_size();

private:
  int get_first_bracket_position();
  void write_EEPROM(unsigned int eeaddress, char data);
  char read_EEPROM(unsigned int eeaddress);

  Logger m_logger;
};

}

#endif //HAL_CONFIGMEMORY_CONTROLLER