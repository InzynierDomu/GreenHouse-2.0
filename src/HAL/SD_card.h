#pragma once

#include "Logger.h"
#include "SD.h"

#include <CRC32.h>
#include <SPI.h>
#include <functional>

namespace HAL
{

class SD_card
{
  public:
  SD_card();
  bool is_card_available() const;
  String get_json_file();
  uint32_t get_crc() const;
  void create_log_file();
  std::function<void(const String&)> get_save_log_callback();

  private:
  Logger m_logger;
  bool m_card_available;
  uint32_t m_crc;
  String m_last_created_file;

  void save_log(const String& log);
};

} // namespace HAL