/**
 * @file Logger.h
 * @brief Logger info, debug, erros to Serial
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */

#pragma once

#include "HAL/Real_clock.h"

#include <map>
#include <string>

enum class Log_type
{
  info, ///< default information log type
  warning, ///< warning log type
  error, ///< error log type
  debug, ///< only debug log type
};

class Logger
{
  public:
  Logger(const String name);
  Logger(const std::string name);
  Logger(const char* name);

  //todo: think about template
  void log(const std::string content, const Log_type type = Log_type::info);
  void log(const String content, const Log_type type = Log_type::info);
  void log(const char* content, const Log_type type = Log_type::info);

  private:
  const String m_module_name; ///< object owner name
  const std::map<Log_type, String> m_msg_type_name{{Log_type::info, "Info"},
                                                   {Log_type::warning, "Warning"},
                                                   {Log_type::error, "Error"},
                                                   {Log_type::debug, "Debug"}}; ///< map wiht log type

  HAL::Real_clock* m_clock;
};