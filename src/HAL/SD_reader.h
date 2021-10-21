#ifndef SDREADER_SCREEN
#define SDREADER_SCREEN

#include "Logger.h"
#include "Pin_config.h"
#include "SD.h"

#include <SPI.h>


namespace HAL
{

class SD_reader
{
  public:
  SD_reader();
  bool is_card_available();
  String get_json_file();
  uint32_t get_crc();

  private:
  Logger m_logger;
  bool m_card_available;
};

} // namespace HAL

#endif // SDREADER_SCREEN
