#include "SD_reader.h"
#include "Logger.h"
#include "Config.h"

namespace HAL{

SD_reader::SD_reader()
{
  m_logger = new Logger("SD reader");
  
  if (!SD.begin(Pins::m_SD_reader_CS)) {
    m_logger->log("Card failed, or not present", Log_type::warning);
    m_card_available = false;
  }    
  else
  {
    m_logger->log("Card Initialized");
    m_card_available = true;
  }
}

bool SD_reader::is_card_available()
{
  return m_card_available;
}

String SD_reader::get_json_file()
{
  File dataFile = SD.open("config.json");
  if (dataFile)
  {
    String json_file;  
    while (dataFile.available()) {
      json_file += (char)dataFile.read();
    }
    dataFile.close();
    return json_file;
  }
  else
  {
    m_logger->log("Config file not found", Log_type::warning);
  }
}

} // namespace HAL