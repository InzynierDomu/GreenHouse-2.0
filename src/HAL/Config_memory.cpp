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
, m_crc(0)
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

  m_logger.log("calculated crc =" + String(m_crc));

  String readed_crc = "";
  for (uint8_t j = 0; j < 10; j++)
  {
    readed_crc += read_EEPROM(i);
    i++;
  }
  m_logger.log("readed crc =" + String(readed_crc));

  if (Utils::Checksum::compare_crc(m_crc, readed_crc))
  {
    m_logger.log("crc is correct");
  }

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

void Config_memory::write_EEPROM(unsigned int eeaddress, const byte data)
{
  byte devaddr = Config::memory_adress | ((eeaddress >> 8) & 0x07);
  byte addr = eeaddress;
  Wire.beginTransmission(devaddr);
  Wire.write(int(addr));
  Wire.write(int(data));
  Wire.endTransmission();
  delay(10);
}

byte Config_memory::read_EEPROM(unsigned int eeaddress)
{
  byte rdata = -1;

  // Three lsb of Device address byte are bits 8-10 of eeaddress
  byte devaddr = Config::memory_adress | ((eeaddress >> 8) & 0x07);
  byte addr = eeaddress;

  Wire.beginTransmission(devaddr);
  Wire.write(int(addr));
  Wire.endTransmission();
  Wire.requestFrom(int(devaddr), 1);
  if (Wire.available())
  {
    rdata = Wire.read();
  }
  return rdata;
}

} // namespace HAL