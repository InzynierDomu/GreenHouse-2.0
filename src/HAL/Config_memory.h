#ifndef HAL_CONFIGMEMORY_CONTROLLER
#define HAL_CONFIGMEMORY_CONTROLLER

#include <Wire.h>

namespace HAL
{

class Config_memory
{
public:
  Config_memory();
  void save_json(String file);
  String get_json();

private:
  void write_EEPROM(unsigned int eeaddress, char data);
  char read_EEPROM(unsigned int eeaddress);
};

}

#endif //HAL_CONFIGMEMORY_CONTROLLER