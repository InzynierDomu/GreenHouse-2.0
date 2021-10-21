#include "Real_clock.h"

namespace HAL
{

Real_clock* Real_clock::m_instance = 0;

Real_clock* Real_clock::get_instance()
{
  if (m_instance == 0)
  {
    m_instance = new Real_clock();
  }
  return m_instance;
}

Real_clock::Real_clock()
: m_rtc(RTC_DS1307())
{
  if (!m_rtc.begin())
  {
    Serial.println("Couldn't find RTC");
  }

  if (!m_rtc.isrunning())
  {
    Serial.println("RTC is not running, need adjust");
  }
}

String Real_clock::get_time()
{
  DateTime time = m_rtc.now();
  // String temp_time = time.timestamp(DateTime::TIMESTAMP_TIME);

  // if(!temp_time.isEmpty())
  // {
  //   m_last_time = temp_time;
  // }

  // return m_last_time;

  return time.timestamp(DateTime::TIMESTAMP_TIME);
}

void Real_clock::adjust(const DateTime data_time)
{
  m_rtc.adjust(data_time);
}

} // namespace HAL