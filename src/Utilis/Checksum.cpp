#include "Checksum.h"

#include <cmath>

namespace Utils
{

void Checksum::add_char(char data)
{
  m_crc.update<char>(data);
}

uint32_t Checksum::calculate_crc()
{
  return m_crc.finalize();
}

String Checksum::fill_crc(const uint32_t crc)
{
  uint8_t crc_lenght = 1;
  if (crc > 0)
  {
    crc_lenght = (int)log10((double)crc) + 1;
  }
  String filled_crc = "";
  for (uint8_t i = 0; i < 10 - crc_lenght; i++)
  {
    filled_crc += "0";
  }
  filled_crc += String(crc);
  return filled_crc;
}

} // namespace Utils