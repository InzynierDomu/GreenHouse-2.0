#pragma once

#include <CRC32.h>

namespace Utils
{

class Checksum
{
  public:
  void add_char(char data);
  uint32_t calculate_crc();

  private:
  CRC32 m_crc;
};

} // namespace Utils