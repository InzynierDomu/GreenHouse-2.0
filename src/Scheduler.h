#pragma once

#include "Logger.h"

#include <functional>

using event = std::pair<long, std::function<void()>>;

// todo: maybe singleton
class Scheduler
{
  public:
  Scheduler();
  void add_action(std::function<void()>, long time);
  void check_events();

  private:
  Logger m_logger; ///< serial logger
  // todo: container for events
};
