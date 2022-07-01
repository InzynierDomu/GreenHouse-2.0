/**
 * @file SD_card.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief sd card handling
 * @date 2022-06
 */
#include "SD_card.h"

#include "Config.h"
#include "Pin_config.h"
#include "Real_clock.h"
#include "Utilis/Checksum.h"

namespace HAL
{

SD_card* SD_card::m_instance = 0;

/**
 * @brief get instance of sd card, create if no instance exist
 * @return instance of sd card
 */
SD_card* SD_card::get_instance()
{
  if (m_instance == 0)
  {
    m_instance = new SD_card();
  }
  return m_instance;
}

SD_card::SD_card()
: m_logger(Logger("SD card", Real_clock::get_instance()->get_time_callback()))
, m_card_available(false)
, m_last_created_file(" ")
{
  if (!SD.begin(Pins::m_SD_reader_CS))
  {
    m_logger.log("Card failed, or not present", Log_type::info);
  }
  else
  {
    m_logger.log("Card Initialized");
    m_card_available = true;
  }
}

/**
 * @brief get inforamation is sd card available
 * @return is sd card available
 */
bool SD_card::is_card_available() const
{
  return m_card_available;
}

/**
 * @brief read configuration json file
 * @return configuration json
 */
String SD_card::get_json_file()
{
  File dataFile = SD.open(Config::m_json_file_name);
  String json_file;
  if (dataFile)
  {
    uint16_t open_bracket_count = 0;
    uint16_t close_bracket_count = 0;

    uint32_t i = 0;

    Utils::Checksum checksum;
    do
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

      json_file += read_character;
      checksum.add_char(read_character);
      i++;
    } while ((open_bracket_count != close_bracket_count || Config::max_json_size > i) && dataFile.available());
    m_crc = checksum.calculate_crc();
    m_logger.log(String(m_crc));
    dataFile.close();
  }
  else
  {
    m_logger.log("Config file not found", Log_type::warning);
  }

  return json_file;
}

/**
 * @brief get crc from json configuration
 * @return crc32
 */
uint32_t SD_card::get_crc() const
{
  return m_crc;
}

/**
 * @brief create log file
 */
void SD_card::create_log_file()
{
  if (m_card_available)
  {
    String file_name = Real_clock::get_instance()->get_date_time_name_format() + ".log";
    File dataFile = SD.open(file_name, FILE_WRITE);
    if (dataFile)
    {
      m_logger.log("Create file");
      dataFile.close();
      m_last_created_file = file_name;
    }
    else
    {
      m_logger.log("problem with create log file", Log_type::error);
    }
  }
}

/**
 * @brief get function to save log on sd
 * @return function to save log on sd
 */
std::function<void(const String&)> SD_card::get_save_log_callback()
{
  return [this](const String& log) { return save_log(log); };
}

void SD_card::save_log(const String& log)
{
  if (m_card_available)
  {
    if (m_last_created_file == " ")
    {
      create_log_file();
    }

    File dataFile = SD.open(m_last_created_file, FILE_WRITE);
    if (dataFile)
    {
      dataFile.println(log);
      dataFile.close();
    }

    if (dataFile.size() > Config::max_log_file_size)
    {
      create_log_file();
    }
  }
}

} // namespace HAL