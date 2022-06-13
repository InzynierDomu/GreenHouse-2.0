#include "Config_memory.h"

#include "Config.h"
#include "Real_clock.h"

namespace HAL
{

Config_memory::Config_memory()
: m_logger(Logger("Config_memory", Real_clock::get_instance()->get_time_callback()))
{}

void Config_memory::save_json(String& file)
{
  for (uint32_t i = 0; i < file.length(); i++)
  {
    write_EEPROM(i, file[i]);
  }
}

String Config_memory::get_json()
{
  String output_file;

  int open_bracket_count = 0;
  int close_bracket_count = 0;

  int i = 0;

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

    if (open_bracket_count > 1)
    {
      // TODO: add to calculate crc
      if ((close_bracket_count - open_bracket_count) == 1)
      {
        // stop adding and calculate
      }
    }

    output_file += read_character;
    i++;
  } while (open_bracket_count != close_bracket_count || Config::max_json_size > i);

  return output_file;
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