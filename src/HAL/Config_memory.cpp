#include "Config_memory.h"

#include "Config.h"

namespace HAL
{

Config_memory::Config_memory():
m_logger(Logger("Config_memory"))
{
}

void Config_memory::save_json(String file)
{
  for(int i =0; i < file.length(); i++ ) 
  {
    write_EEPROM(i, file[i]);
  }
}

String Config_memory::get_json()
{
  m_logger.log("get_json" , Log_type::debug);
  // get_json_size();
  String output_file;

  int open_bracket_count = 0;
  int close_bracket_count = 0;

  int i = get_first_bracket_position();

  do
  {
    char read_character = read_EEPROM(i);
    if( read_character == '{')
    {
      open_bracket_count++;
    }
    else if(read_character == '}')    
    {
      close_bracket_count++;
    }

    output_file+=read_character;
    i++;
  }while (open_bracket_count != close_bracket_count && Config::max_json_size > i );

  return output_file;
}

String Config_memory::get_raw_file()
{
  m_logger.log("get_raw" , Log_type::debug);
  String output_file;
  int first_bracket_position = get_first_bracket_position();
  for (int i = 0; i < first_bracket_position; i++)
  {
    output_file += read_EEPROM(i);
  }
  output_file += get_json();
  return output_file;
}

int Config_memory::get_json_size()
{
  int open_bracket_count = 0;
  int close_bracket_count = 0;
  int i = get_first_bracket_position();

  do
  {
    char read_character = read_EEPROM(i);
    if( read_character == '{')
    {
      open_bracket_count++;
    }
    else if(read_character == '}')    
    {
      close_bracket_count++;
    }
    i++;
  }while (open_bracket_count != close_bracket_count && Config::max_json_size > i );
  m_logger.log("json size=" + String(i) , Log_type::debug);
  return i;
}

int Config_memory::get_first_bracket_position()
{
  for(int i = 0; 100 > i; i++)
  {
    if(read_EEPROM(i) == '{')
    {
      if(read_EEPROM(i + 1) == '"')
      {
        m_logger.log("first bracket position=" +String(i) , Log_type::debug);
        return i;
      }      
    }
  }
}

void Config_memory::write_EEPROM(unsigned int eeaddress, char data)
{
  Wire.beginTransmission(Config::memory_adress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();

  delay(5);
}

char Config_memory::read_EEPROM(unsigned int eeaddress)
{
  char rdata = '0';

  Wire.beginTransmission(Config::memory_adress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(Config::memory_adress ,1);

  if (Wire.available()) rdata = Wire.read();
 
  return rdata;
}

}