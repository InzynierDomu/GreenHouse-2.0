/**
 * @file SenderReceiver.cpp
 * @brief controlling sending and receiving messages peripherals-MQTT
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */

#include "SenderReceiver.h"
#include "Logger.h"

/**
 * @brief constructor
 * @param preipherals: pointer to preipherals
 * @param client: pointer to MQTT client
 */
SenderReceiver::SenderReceiver(std::unique_ptr<Peripherals::Peripherals_generator> preipherals, PubSubClient* client):
m_logger(Logger("Sender and reciver")),
m_peripherals(std::move(preipherals)),
m_client(client)
{
  // m_logger = new Logger("Sender and reciver");
}

void SenderReceiver::publish()
{
  auto mulitsensor = m_peripherals->get_multisensor();
  mulitsensor->publish(m_client);
}

void SenderReceiver::callback(const char* topic, byte* payload, unsigned int length)
{
  m_logger.log("Message arrived");
  auto output = m_peripherals->get_output(topic); 
  if(output)
  {
    (*output)->set_value(*payload);  
  }
}

std::function<void(const char*, byte*, unsigned int)> SenderReceiver::get_callback()
{
  return [this](const char* _topic, byte* _payload, unsigned int _lenght){callback(_topic, _payload, _lenght);};
}

