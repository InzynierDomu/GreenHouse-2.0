#include "Config_memory.h"

#include "Config.h"
#include "Logger.h"

namespace HAL
{

Config_memory::Config_memory()
{
  m_logger = new Logger("Config_memory");
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
  }while (open_bracket_count != close_bracket_count && 1024 > i );

  return output_file;
}

String Config_memory::get_raw_file()
{
  String output_file;
  int first_bracket_position = get_first_bracket_position();
  for (int i = 0; i < first_bracket_position; i++)
  {
    output_file += read_EEPROM(i);
  }
  output_file += get_json();
  return output_file;
}

int Config_memory::get_first_bracket_position()
{
  for(int i = 0; 100 > i; i++)
  {
    if(read_EEPROM(i) == '{')
    {
      if(read_EEPROM(i + 1) == '"')
      {
        return i;
      }      
    }
  }
}

void Config_memory::write_EEPROM(unsigned int eeaddress, char data)
{
  Wire.beginTransmission(Config::m_memory_adress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();

  delay(5);
}

char Config_memory::read_EEPROM(unsigned int eeaddress)
{
  char rdata = '0';

  Wire.beginTransmission(Config::m_memory_adress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(Config::m_memory_adress ,1);

  if (Wire.available()) rdata = Wire.read();
 
  return rdata;
}

}