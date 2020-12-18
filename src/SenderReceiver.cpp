#include "SenderReceiver.h"
#include "Logger.h"

SenderReceiver::SenderReceiver(Peripherals::Peripherals_generator* preipherals):
m_preipherals(preipherals)
{
  m_logger = new Logger("Sender and reciver");
}

void SenderReceiver::publish()
{

}

void SenderReceiver::callback(const char* topic, byte* payload, unsigned int length)
{
  m_logger->log("Message!");
}

std::function<void(const char*, byte*, unsigned int)> SenderReceiver::get_callback()
{
  return [this](const char* _topic, byte* _payload, unsigned int _lenght){callback(_topic, _payload, _lenght);};
}

