#ifndef HAL_REALCLOCK_CONTROLLER
#define HAL_REALCLOCK_CONTROLLER

#include "RTClib.h"

#include <Arduino.h>

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

#endif // HAL_REALCLOCK_CONTROLLER