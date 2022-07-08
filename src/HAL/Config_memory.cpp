/**
 * @file Config_memory.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief EEPROM handling for JSON configuration
 * @date 2022-06
 */
#include "Config_memory.h"

#include "Config.h"
#include "Real_clock.h"
#include "Utilis/Checksum.h"

namespace HAL
{

/**
 * @brief Construct a new Config_memory::Config_memory object
 */
Config_memory::Config_memory()
: m_logger(Logger("Config_memory", Real_clock::get_instance()->get_time_callback()))
{}

/**
 * @brief save json file on eeprom
 * @param file: file to save
 */
void Config_memory::save_json(String& file)
{
  for (uint32_t i = 0; i < file.length(); i++)
  {
    write_EEPROM(i, file[i]);
  }
}

/**
 * @brief get configuration json file from eeprom
 * @return configuration json
 */
String Config_memory::get_json()
{
  String output_file;

  uint16_t open_bracket_count = 0;
  uint16_t close_bracket_count = 0;

  uint32_t i = 0;

  Utils::Checksum checksum;

  do
  {
    char read_character = read_EEPROM(i);
    if (read_character == '{')
    {
      open_bracket_count++;
    }
    else if (read_character == '}')
    {
      close_bracket_count++;
    }

    output_file += read_character;
    checksum.add_char(read_character);
    i++;
  } while (open_bracket_count != close_bracket_count || Config::max_json_size > i);
  m_crc = checksum.calculate_crc();
  m_logger.log(String(m_crc));

  return output_file;
}

/**
 * @brief get crc32 from configuration json, after read json
 * @return json crc32
 */
uint32_t Config_memory::get_crc() const
{
  return m_crc;
}

void Config_memory::write_EEPROM(unsigned int eeaddress, char data)
{
  Wire.beginTransmission(Config::memory_adress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();

  delay(5);
}

char Config_memory::read_EEPROM(unsigned int eeaddress)
{
  char rdata = '0';

  Wire.beginTransmission(Config::memory_adress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(Config::memory_adress, 1);

  if (Wire.available())
    rdata = Wire.read();

  return rdata;
}

} // namespace HAL