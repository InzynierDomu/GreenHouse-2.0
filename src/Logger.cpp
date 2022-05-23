#include "Logger.h"

/**
 * @brief constructor
 * @param name: object owner name
 */
Logger::Logger(const std::string name, std::function<time_t()> get_time)
: m_module_name(name.c_str())
, m_get_time(get_time)
{
  print_create();
}

/**
 * @brief constructor
 * @param name: object owner name
 */
Logger::Logger(const String name, std::function<time_t()> get_time)
: m_module_name(name)
, m_get_time(get_time)
{
  print_create();
}

/**
 * @brief constructor
 * @param name: object owner name
 */
Logger::Logger(const char* name, std::function<time_t()> get_time)
: m_module_name(name)
, m_get_time(get_time)
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
    print_type(type);
    Serial.println(content.c_str());
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
    print_type(type);
    Serial.println(content);
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
    print_type(type);
    Serial.println(content);
#ifndef DEBUG
  }
#endif
}

void Logger::print_create()
{
  Serial.print(get_time());
  Serial.print("::");
  Serial.println(m_module_name + "::create logger");
}

void Logger::print_type(const Log_type type)
{
  Serial.print(get_time());
  Serial.print("::");
  Serial.print(m_module_name);
  Serial.print("::");
  auto it = m_msg_type_name.find(type);
  Serial.print(it->second);
  Serial.print("::");
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