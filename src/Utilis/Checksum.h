#pragma once

#include <CRC32.h>

namespace Utils
{

class Checksum
{
  public:
  void add_char(char data);
  uint32_t calculate_crc();
  static String fill_crc(const uint32_t crc);

  private:
  CRC32 m_crc;
};

} // namespace Utils