#include "Checksum.h"

#include <cmath>

namespace Utils
{

/**
 * @brief add character to crc calculation base
 * @param data charcter
 */
void Checksum::add_char(char data)
{
  m_crc.update<char>(data);
}

/**
 * @brief calculate crc from data
 * @return crc32
 */
uint32_t Checksum::calculate_crc()
{
  return m_crc.finalize();
}

/**
 * @brief compare calculated and readed crc
 * @param crc calculated crc
 * @param crc_readed crc readed from text, filled to 10 digits
 * @return is crc is the same
 */
bool Checksum::compare_crc(const uint32_t crc, String& crc_readed)
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
  return (filled_crc == crc_readed);
}

} // namespace Utils