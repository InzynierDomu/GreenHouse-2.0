#include "Scheduler.h"

#include "HAL/Real_clock.h"

Scheduler::Scheduler()
: m_logger(Logger("Scheduler", HAL::Real_clock::get_instance()->get_time_callback()))
{}

void Scheduler::add_action(std::function<void()>, long time)
{
  // add event to container
}

void Scheduler::check_events()
{
  // check event in conteiner
}