#include "Real_clock.h"

namespace HAL
{

Real_clock::Real_clock():
m_rtc(RTC_DS1307())
{
  m_rtc.begin();
}

String Real_clock::get_time()
{
  DateTime time = m_rtc.now();
  return time.timestamp(DateTime::TIMESTAMP_TIME);
}

void Real_clock::adjust(const DateTime data_time)
{
  m_rtc.adjust(data_time);
}

}