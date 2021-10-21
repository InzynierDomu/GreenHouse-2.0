/**
 * @file Logger.h
 * @brief Logger info, debug, erros to Serial
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */

#ifndef LOGGER
#define LOGGER

#include "HAL/Real_clock.h"

#include <Arduino.h>
#include <map>

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
  Logger(String name);
  void log(const String content, const Log_type type = Log_type::info);

  private:
  const String m_module_name; ///< object owner name
  const std::map<Log_type, String> m_msg_type_name{{Log_type::info, "Info"},
                                                   {Log_type::warning, "Warning"},
                                                   {Log_type::error, "Error"},
                                                   {Log_type::debug, "Debug"}}; ///< map wiht log type

  HAL::Real_clock* m_clock;
};

#endif // LOGGER