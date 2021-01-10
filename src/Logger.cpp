#include "Logger.h"

Logger::Logger(String name):
m_module_name(name)
{
    Serial.println(name + "::create logger");
}

void Logger::log(const String content, const Msg_type type)
{
    Serial.print(m_module_name);
    Serial.print("::");
    auto it = m_msg_type_name.find(type);
    Serial.print(it->second);
    Serial.print("::");
    Serial.println(content);
}