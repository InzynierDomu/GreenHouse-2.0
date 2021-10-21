#include "SD_reader.h"

#include "Config.h"


namespace HAL
{

SD_reader::SD_reader()
: m_logger(Logger("SD reader"))
{
  if (!SD.begin(Pins::m_SD_reader_CS))
  {
    m_logger.log("Card failed, or not present", Log_type::warning);
    m_card_available = false;
  }
  else
  {
    m_logger.log("Card Initialized");
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
    while (dataFile.available())
    {
      json_file += (char)dataFile.read();
    }
    dataFile.close();
    return json_file;
  }
  else
  {
    m_logger.log("Config file not found", Log_type::warning);
  }
}

uint32_t SD_reader::get_crc()
{
  File dataFile = SD.open("config.json");
  int open_bracket_count = 0;
  int close_bracket_count = 0;
  String crc;
  if (dataFile)
  {
    while (dataFile.available())
    {
      char read_character = (char)dataFile.read();
      if (read_character == '{')
      {
        open_bracket_count++;
      }
      else if (read_character == '}')
      {
        close_bracket_count++;
      }
      else if (open_bracket_count == close_bracket_count)
      {
        crc += read_character;
      }
    }
  }
  dataFile.close();
  return (uint32_t)strtoul(&crc[0], nullptr, 16); // todo
}

} // namespace HAL