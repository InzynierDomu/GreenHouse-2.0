#include "Real_clock.h"
#include "RTClib.h"

namespace HAL
{

Real_clock::Real_clock()
{
  m_rtc = new RTC_DS1307();
  m_rtc->begin();
}

String Real_clock::get_time()
{
  DateTime time = m_rtc->now();
  return time.timestamp(DateTime::TIMESTAMP_TIME);
}

}