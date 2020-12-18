#include "SD_reader.h"
#include "Logger.h"

namespace HAL{

SD_reader::SD_reader()
{
  m_logger = new Logger("SD reader");
  
  if (!SD.begin(Pins::m_SD_reader_CS)) {
    m_logger->log("Card failed, or not present", Msg_type::warning);
  }    
}

} // namespace HAL