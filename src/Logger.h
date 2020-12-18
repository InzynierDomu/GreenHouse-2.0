#ifndef LOGGER
#define LOGGER

#include <Arduino.h>
#include <map>

enum class Msg_type{
info,
warning,
error
};

class Logger
{
public:
    Logger(String name);
    void log(const String content, const Msg_type type = Msg_type::info);

private:
    const String m_module_name;
    const std::map<Msg_type, String> m_msg_type_name{
    {Msg_type::info, "Info"},
    {Msg_type::warning, "Warning"},
    {Msg_type::error, "Error"}};
};

#endif //LOGGE