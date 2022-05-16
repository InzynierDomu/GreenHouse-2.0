#include "Config_memory.h"

#include "Config.h"
#include "Real_clock.h" 

namespace HAL
{

Config_memory::Config_memory()
: m_logger(Logger("Config_memory", Real_clock::get_instance()->get_time_callback())) //,
// m_stream(std::ostream(buf))
{}

void Config_memory::save_json(String file)
{
  for (int i = 0; i < file.length(); i++)
  {
    write_EEPROM(i, file[i]);
  }
}

// todo: chagne to stream
// check first char == {
// check lenght < max size
// check crc

String Config_memory::get_json()
{
  // get_json_size();
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

    output_file += read_character;
    i++;
  } while (open_bracket_count != close_bracket_count || Config::max_json_size > i);

  String crc;
  const int crc_lenght = i + 8;
  for (i; i < crc_lenght; i++)
  {
    char read_character = read_EEPROM(i);
    crc += read_character;
  }
  m_crc = crc.toInt();
  m_logger.log("crc from memory = " + crc);
  m_logger.log("crc from memory = " + String(m_crc));

  return output_file;
}

// String Config_memory::get_raw_file()
// {
//   m_logger.log("get_raw" , Log_type::debug);
//   String output_file;
//   int first_bracket_position = 0;
//   for (int i = 0; i < first_bracket_position; i++)
//   {
//     output_file += read_EEPROM(i);
//   }
//   output_file += get_json();
//   return output_file;
// }

int Config_memory::get_json_size()
{
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
    i++;
  } while (open_bracket_count != close_bracket_count && Config::max_json_size > i);
  m_logger.log("json size=" + String(i));
  return i;
}

// todo: chagne to stream
// test
// std::ostream* Config_memory::get_stream()
// {
//   return &m_stream;
// }

// bool Config_memory::stream()
// {
//   char bracket = '{';
//   m_stream<<bracket;
//   return true;
// }

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