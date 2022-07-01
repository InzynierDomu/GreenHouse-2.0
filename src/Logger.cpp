/**
 * @file Logger.cpp
 * @brief Logger info, debug, erros to Serial
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @date 01-2021
 */
#include "Logger.h"

/**
 * @brief constructor
 * @param name: object owner name
 * @param get_time: function to get timestamp
 * @param save: function call whenever log is call
 */
Logger::Logger(const std::string name, std::function<time_t()> get_time, std::function<void(const String&)> save)
: m_module_name(name.c_str())
, m_get_time(get_time)
, m_saving_callback(save)
{
  print_create();
}

/**
 * @brief constructor
 * @param name: object owner name
 * @param get_time: function to get timestamp
 * @param save: function call whenever log is call
 */
Logger::Logger(const String name, std::function<time_t()> get_time, std::function<void(const String&)> save)
: m_module_name(name)
, m_get_time(get_time)
, m_saving_callback(save)
{
  print_create();
}

/**
 * @brief constructor
 * @param name: object owner name
 * @param get_time: function to get timestamp
 * @param save: function call whenever log is call
 */
Logger::Logger(const char* name, std::function<time_t()> get_time, std::function<void(const String&)> save)
: m_module_name(name)
, m_get_time(get_time)
, m_saving_callback(save)
{
  print_create();
}

/**
 * @brief Print log on serial
 * @param content main content of log
 * @param type log type, default = info
 */
void Logger::log(const std::string& content, const Log_type type)
{
#ifndef DEBUG
  if (type != Log_type::debug)
  {
#endif
    print_log(content.c_str(), type);
#ifndef DEBUG
  }
#endif
}

/**
 * @brief Print log on serial
 * @param content main content of log
 * @param type log type, default = info
 */
void Logger::log(const char* content, const Log_type type)
{
#ifndef DEBUG
  if (type != Log_type::debug)
  {
#endif
    print_log(content, type);
#ifndef DEBUG
  }
#endif
}

/**
 * @brief Print log on serial
 * @param content main content of log
 * @param type log type, default = info
 */
void Logger::log(const String& content, const Log_type type)
{
#ifndef DEBUG
  if (type != Log_type::debug)
  {
#endif
    print_log(content, type);
#ifndef DEBUG
  }
#endif
}

/**
 * @brief set callback for saving log to another place
 * @param callback function call whenever log is call
 */
void Logger::set_saving_callback(std::function<void(const String&)> callback)
{
  m_saving_callback = callback;
}

void Logger::print_create()
{
  String output = get_time();
  output += "::";
  output += m_module_name;
  output += "::create logger";
  Serial.println(output);
  if (m_saving_callback)
  {
    m_saving_callback(output);
  }
}

void Logger::print_log(const String& content, const Log_type type)
{
  String log = get_preamble(type);
  log += content;
  Serial.println(log);
  if (m_saving_callback)
  {
    m_saving_callback(log);
  }
}

String Logger::get_preamble(const Log_type type)
{
  String output = get_time();
  output += "::";
  output += m_module_name;
  output += "::";
  auto it = m_msg_type_name.find(type);
  output += it->second;
  output += "::";
  return output;
}

String Logger::get_time()
{
  if (m_get_time != nullptr)
  {
    auto now = m_get_time();
    std::tm tm = *std::localtime(&now);
    String time_formated = String(tm.tm_hour) + ":" + String(tm.tm_min) + ":" + String(tm.tm_sec);
    return time_formated;
  }
  else
  {
    return "0:0:0";
  }
}