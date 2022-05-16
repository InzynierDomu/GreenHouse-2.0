#pragma once

#include "RTClib.h"

#include <functional>
#include <time.h>

namespace HAL
{

class Real_clock
{
  public:
  static Real_clock* get_instance();
  String get_time();
  std::function<time_t()> get_time_callback();
  void adjust(const DateTime& data_time);

  protected:
  Real_clock();

  private:
  static Real_clock* m_instance;
  RTC_DS1307 m_rtc;

  time_t get_raw_time();
};

} // namespace HAL