#include "Logger.h"

/**
 * @brief constructor
 * @param name: object owner name
 */
Logger::Logger(String name)
: m_module_name(name)
, m_clock(HAL::Real_clock::get_instance())
{
  Serial.print(m_clock->get_time());
  Serial.print("::");
  Serial.println(m_module_name + "::create logger");
}

/**
 * @brief Print log on serial
 * @param content main content of log
 * @param type log type, default = info
 */
void Logger::log(const String content, const Log_type type)
{
#ifndef DEBUG
  if (type != Log_type::debug)
  {
#endif
    Serial.print(m_clock->get_time());
    Serial.print("::");
    Serial.print(m_module_name);
    Serial.print("::");
    auto it = m_msg_type_name.find(type);
    Serial.print(it->second);
    Serial.print("::");
    Serial.println(content);
#ifndef DEBUG
  }
#endif
}