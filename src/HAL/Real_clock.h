/**
 * @file Real_clock.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Real time clock handling (singleton)
 * @date 2022-06
 */
#pragma once

#include "RTClib.h"

#include "Logger.h"
#include <ctime>
#include <functional>

namespace HAL
{

class Real_clock
{
  public:
  static Real_clock* get_instance();
  String get_time();
  String get_date_time_name_format();
  std::function<time_t()> get_time_callback();
  void adjust(const time_t data_time);

  protected:
  Real_clock();

  private:
  static Real_clock* m_instance; ///< instanse of singleton
  RTC_DS1307 m_rtc; ///< RTC DS1307
  Logger m_logger; ///< logger

  time_t get_raw_time();
};

} // namespace HAL