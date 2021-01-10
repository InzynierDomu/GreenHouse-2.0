#ifndef HAL_REALCLOCK_CONTROLLER
#define HAL_REALCLOCK_CONTROLLER

#include <Arduino.h>

class RTC_DS1307;

namespace HAL
{

class Real_clock
{
public:
  Real_clock();
  String get_time();

private:
  RTC_DS1307* m_rtc;
};

}

#endif //HAL_REALCLOCK_CONTROLLER