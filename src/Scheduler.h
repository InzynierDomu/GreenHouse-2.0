#pragma once

#include "Logger.h"

#include <functional>
#include <map>

// todo: maybe singleton
class Scheduler
{
  public:
  Scheduler();
  void add_action(std::function<void()> callback, long time);
  void check_events(long now);

  private:
  Logger m_logger; ///< serial logger
  std::map<long, std::function<void()>> m_events;
};
