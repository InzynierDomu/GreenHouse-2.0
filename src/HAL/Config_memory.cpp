#include "Config_memory.h"
#include "Config.h"

namespace HAL
{

Config_memory::Config_memory()
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
  String output_file;
  output_file += read_EEPROM(0);
  output_file += read_EEPROM(1);
  return output_file;
}

void Config_memory::write_EEPROM(unsigned int eeaddress, char data)
{
  Wire.beginTransmission(Config::m_memory_adress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
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