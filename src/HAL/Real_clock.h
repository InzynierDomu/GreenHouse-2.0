#ifndef HAL_REALCLOCK_CONTROLLER
#define HAL_REALCLOCK_CONTROLLER

#include <Arduino.h>

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
  RTC_DS1307 m_rtc;
};

}

#endif //HAL_REALCLOCK_CONTROLLER