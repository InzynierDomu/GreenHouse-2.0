/**
 * @file Real_clock.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Real time clock (singleton)
 * @date 2022-06
 */

#include "Real_clock.h"

namespace HAL
{

Real_clock* Real_clock::m_instance = 0;

/**
 * @brief get instance of real clock, create if no instance exist
 * @return Real_clock* instance of real clock
 */
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

/**
 * @brief get actual time from clock
 * @return String timestamp
 */
String Real_clock::get_time()
{
  auto time = m_rtc.now();
  return time.timestamp(DateTime::TIMESTAMP_TIME);
}

/**
 * @brief get getter time function
 * @return std::function<time_t()> getter raw time
 */
std::function<time_t()> Real_clock::get_time_callback()
{
  return [this]() { return get_raw_time(); };
}

/**
 * @brief adjust clock time
 * @param data_time: time to set
 */
void Real_clock::adjust(const time_t data_time)
{
  auto time = DateTime(data_time);
  Serial.println("set time: " + String(time.hour()) + ":" + String(time.minute()) + ":" + String(time.second()));
  m_rtc.adjust(time);
  auto now = m_rtc.now();
  long time_dif = now.unixtime() - data_time;
  if (abs(time_dif) > 100)
  {
    Serial.println("error in time adjust");
  }
}

time_t Real_clock::get_raw_time()
{
  auto time = m_rtc.now();
  return time.unixtime();
}

} // namespace HAL