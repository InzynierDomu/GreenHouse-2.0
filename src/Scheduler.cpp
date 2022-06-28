/**
 * @file Scheduler.cpp
 * @brief scheduling action on outputs
 * @author by Szymon Markiewicz (http://www.inzynierdomu.pl/)
 * @date 01-2021
 */
#include "Scheduler.h"

#include "HAL/Real_clock.h"

/**
 * @brief Construct a new Scheduler:: Scheduler object
 */
Scheduler::Scheduler()
: m_logger(Logger("Scheduler", HAL::Real_clock::get_instance()->get_time_callback()))
{}

/**
 * @brief schedul new event in list
 * @param callback event
 * @param time time when run event
 */
void Scheduler::add_action(std::function<void()> callback, uint8_t time)
{
  m_logger.log("Add event to scheduler");
  long finish_time = (millis() / 1000L) + time;
  m_events.insert({finish_time, callback});
}

/**
 * @brief check if run event
 * @param now timestamp
 */
void Scheduler::check_events(long now)
{
  if (!m_events.empty())
  {
    auto event = m_events.find(now / 1000L); // TODO: maybe the same time or after run time
    if (event != m_events.end())
    {
      m_logger.log("Scheduled event", Log_type::debug);
      auto callback = event->second;
      try
      {
        callback();
      }
      catch (const std::bad_function_call& error)
      {
        m_logger.log(error.what(), Log_type::debug);
      }
      m_events.erase(event->first); // FIXME: not best-> situation when 2 action finish in the same time, check before erase is more than one
                                    // event with that key
    }
  }
}