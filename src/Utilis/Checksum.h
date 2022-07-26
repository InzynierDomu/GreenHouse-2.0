#pragma once

#include <CRC32.h>

namespace Utils
{

class Checksum
{
  public:
  void add_char(char data);
  uint32_t calculate_crc();
  static bool compare_crc(const uint32_t crc, String& crc_readed);

  private:
  CRC32 m_crc; ///< crc32 calculation
};

} // namespace Utils