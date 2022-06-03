/**
 * @file SenderReceiver.h
 * @brief controlling sending and receiving messages peripherals-MQTT
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */

#pragma once

#include "Logger.h"
#include "Peripherals/Peripherals.h"

#include <memory>

class SenderReceiver
{
  public:
  SenderReceiver(std::unique_ptr<Peripherals::Peripherals> preipherals, PubSubClient& client);
  void publish();
  std::function<void(const char*, byte*, unsigned int)> get_callback();

  private:
  Logger m_logger; ///< serial logger
  std::unique_ptr<Peripherals::Peripherals> m_peripherals; ///< peripherals inputs/outputs
  PubSubClient& m_client; ///< MQTT client

  void callback(const char* topic, byte* payload, unsigned int length);
};