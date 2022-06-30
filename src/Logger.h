/**
 * @file Logger.h
 * @brief Logger info, debug, erros to Serial
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @date 01-2021
 */
#pragma once

#include <Arduino.h>
#include <ctime>
#include <functional>
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
  Logger(const String name, std::function<time_t()> get_time = nullptr, std::function<void(const String&)> save = nullptr);
  Logger(const std::string name, std::function<time_t()> get_time = nullptr, std::function<void(const String&)> save = nullptr);
  Logger(const char* name, std::function<time_t()> get_time = nullptr, std::function<void(const String&)> save = nullptr);

  void log(const std::string& content, const Log_type type = Log_type::info);
  void log(const String& content, const Log_type type = Log_type::info);
  void log(const char* content, const Log_type type = Log_type::info);
  void set_saving_callback(std::function<void(const String&)> callback);

  private:
  void print_create();
  void print_log(const String& content, const Log_type type);
  String get_preamble(const Log_type type);
  String get_time();

  const String m_module_name; ///< object owner name
  std::function<time_t()> m_get_time; ///< function to get timestamp
  std::function<void(const String&)> m_saving_callback; ///< additional function in logging

  const std::map<Log_type, String> m_msg_type_name{{Log_type::info, "Info"},
                                                   {Log_type::warning, "Warning"},
                                                   {Log_type::error, "Error"},
                                                   {Log_type::debug, "Debug"}}; ///< map wiht log type                                                
};