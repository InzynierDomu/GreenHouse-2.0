/**
 * @file Real_clock.h
 * @brief Logger info, debug, erros to Serial
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */

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
  auto time = m_rtc.now();
  return time.timestamp(DateTime::TIMESTAMP_TIME);
}

time_t Real_clock::get_raw_time()
{
  auto time = m_rtc.now();
  return time.unixtime();
}

std::function<time_t()> Real_clock::get_time_callback()
{
  return [this](){ return get_raw_time(); };
}

void Real_clock::adjust(const time_t data_time)
{
  auto time = DateTime(data_time);
  Serial.println("set time: " + String(time.hour()) + ":" + String(time.minute()) + ":" + String(time.second()));
  m_rtc.adjust(time);
  auto now = m_rtc.now();
  if(abs(now.unixtime() - data_time) > 100)
  {
    Serial.println("error in time adjust");
  }
}

} // namespace HAL