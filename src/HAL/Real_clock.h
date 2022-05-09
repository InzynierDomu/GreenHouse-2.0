#pragma once

#include "RTClib.h"

namespace HAL
{

class Real_clock
{
  public:
  static Real_clock* get_instance();
  String get_time();
  void adjust(const DateTime data_time);

  protected:
  Real_clock();

  private:
  static Real_clock* m_instance;
  // String m_last_time;
  RTC_DS1307 m_rtc;
};

} // namespace HAL