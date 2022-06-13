#include "SD_reader.h"

#include "Config.h"
#include "Pin_config.h"
#include "Real_clock.h"

namespace HAL
{

SD_reader::SD_reader()
: m_logger(Logger("SD reader", Real_clock::get_instance()->get_time_callback()))
, m_card_available(false)
{
  if (!SD.begin(Pins::m_SD_reader_CS))
  {
    m_logger.log("Card failed, or not present", Log_type::warning);
  }
  else
  {
    m_logger.log("Card Initialized");
    m_card_available = true;
  }
}

bool SD_reader::is_card_available() const
{
  return m_card_available;
}

String SD_reader::get_json_file()
{
  File dataFile = SD.open("config.json");
  String json_file;
  if (dataFile)
  {
    int open_bracket_count = 0;
    while (dataFile.available())
    {
      char read_character = (char)dataFile.read();
      if (open_bracket_count > 1)
      {
        // TODO: add to calculate crc
      }
      else if (read_character == '{')
      {
        open_bracket_count++;
      }

      json_file += read_character;
    }
    dataFile.close();
  }
  else
  {
    m_logger.log("Config file not found", Log_type::warning);
  }

  return json_file;
}

bool SD_reader::compare_crc(String crc_from_json, CRC32& crc_calculated)
{
  m_logger.log("crc from json" + crc_from_json, Log_type::debug);
  m_logger.log("crc calculated" + String(crc_calculated.finalize()), Log_type::debug);
  uint32_t crc = (uint32_t)strtoul(&crc_from_json[0], nullptr, 16);

  if (crc_calculated.finalize() == crc)
  {
    m_logger.log("Bad crc compare", Log_type::error);
    return true;
  }

  return false;
}

} // namespace HAL