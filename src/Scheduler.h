/**
 * @file Scheduler.h
 * @brief scheduling action on outputs
 * @author by Szymon Markiewicz (http://www.inzynierdomu.pl/)
 * @date 01-2021
 */
#pragma once

#include "Logger.h"

#include <functional>
#include <map>

// TODO: maybe singleton
class Scheduler
{
  public:
  Scheduler();
  void add_action(std::function<void()> callback, uint8_t time);
  void check_events(long now);

  private:
  Logger m_logger; ///< serial logger
  std::map<long, std::function<void()>> m_events; ///< scheduled events
};
