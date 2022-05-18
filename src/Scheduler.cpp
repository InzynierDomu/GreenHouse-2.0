#include "Scheduler.h"

#include "HAL/Real_clock.h"

Scheduler::Scheduler()
: m_logger(Logger("Scheduler", HAL::Real_clock::get_instance()->get_time_callback()))
{}

void Scheduler::add_action(std::function<void()> callback, long time)
{
  m_logger.log("Add event to scheduler");
  long finish_time = (millis() / 1000) + time;
  m_events.insert({finish_time, callback});
}

void Scheduler::check_events(long now)
{
  if (!m_events.empty())
  {
    auto event = m_events.find(now / 1000L);
    if (event->second != NULL)
    {
      m_logger.log("found!", Log_type::debug);
      event->second();
      m_events.erase(event->first);
    }
  }
}