/**
 * @file SenderReceiver.cpp
 * @brief controlling sending and receiving messages peripherals-MQTT
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */

#include "SenderReceiver.h"

#include "HAL/Real_clock.h"

/**
 * @brief constructor
 * @param preipherals: pointer to preipherals
 * @param client: pointer to MQTT client
 */
SenderReceiver::SenderReceiver(std::unique_ptr<Peripherals::Peripherals> preipherals, PubSubClient& client)
: m_logger(Logger("Sender and reciver", HAL::Real_clock::get_instance()->get_time_callback()))
, m_peripherals(std::move(preipherals))
, m_client(client)
{}

void SenderReceiver::publish()
{
  m_logger.log("Publish");

  for (auto it = (m_peripherals->m_inputs).begin(); it != (m_peripherals->m_inputs).end(); it++)
  {
    (*it)->publish(m_client);
  }
}

void SenderReceiver::callback(const char* topic, byte* payload, unsigned int length)
{
  m_logger.log("Message arrived");
  auto output = m_peripherals->get_output(topic);
  String msg_payload = String((char*)payload);
  m_logger.log("Msg payload = " + msg_payload);
  if (output != nullptr)
  {
    output->set_value(msg_payload.toInt());
  }
}

std::function<void(const char*, byte*, unsigned int)> SenderReceiver::get_callback()
{
  return [this](const char* _topic, byte* _payload, unsigned int _lenght) { callback(_topic, _payload, _lenght); };
}
