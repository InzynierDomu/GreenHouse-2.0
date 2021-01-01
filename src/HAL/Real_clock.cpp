#include "Real_clock.h"
#include "RTClib.h"

namespace HAL
{

Real_clock::Real_clock()
{
    m_rtc = new RTC_DS1307();
}

}