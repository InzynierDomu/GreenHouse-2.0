#ifndef SDREADER_SCREEN
#define SDREADER_SCREEN

#include "Logger.h"
#include "Pin_config.h"
#include "SD.h"

#include <CRC32.h>
#include <SPI.h>

namespace HAL
{

class SD_reader
{
  public:
  SD_reader();
  bool is_card_available() const;
  String get_json_file(); 

  private:
  Logger m_logger;
  bool m_card_available;

  bool compare_crc(String crc_from_json, CRC32& crc_calculated);
};

} // namespace HAL

#endif // SDREADER_SCREEN
