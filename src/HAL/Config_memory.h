#ifndef HAL_CONFIGMEMORY_CONTROLLER
#define HAL_CONFIGMEMORY_CONTROLLER

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
  void save_json(String file);
  String get_json();
  // String get_raw_file();
  int get_json_size();

  // todo: add check function before parse
  // todo: chagne to stream
  // std::ostream* get_stream();
  // bool stream();

  private:
  void write_EEPROM(unsigned int eeaddress, char data);
  char read_EEPROM(unsigned int eeaddress);

  Logger m_logger;
  int m_crc;

  // todo: chagne to stream
  // char* buf;
  // std::ostream m_stream;
};

} // namespace HAL

#endif // HAL_CONFIGMEMORY_CONTROLLER