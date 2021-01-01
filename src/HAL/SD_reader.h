#ifndef SDREADER_SCREEN
#define SDREADER_SCREEN

#include <SPI.h>
#include "SD.h"
#include "Pin_config.h"

class Logger;

namespace HAL{

class SD_reader
{
public:
  SD_reader();
  bool is_card_available();
  String get_json_file();

private:
  Logger* m_logger;
  bool m_card_available;
};

} // namespace HAL

#endif // SDREADER_SCREEN
