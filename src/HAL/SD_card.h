/**
 * @file SD_card.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief sd card handling
 * @date 2022-06
 */
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
  static SD_card* get_instance();
  bool is_card_available() const;
  String get_json_file();
  uint32_t get_crc() const;
  void create_log_file();
  std::function<void(const String&)> get_save_log_callback();

  protected:
  SD_card();

  private:
  static SD_card* m_instance; ///< instanse of singleton
  Logger m_logger; ///< logger
  bool m_card_available; ///< is card available
  uint32_t m_crc; ///< json crc
  String m_last_created_file; ///< last created log file name

  void save_log(const String& log);
};

} // namespace HAL