/**
 * @file SenderReceiver.h
 * @brief controlling sending and receiving messages peripherals-MQTT
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */

#pragma once

#include "Peripherals/Peripherals_generator.h"

#include <memory>

class Logger;

class SenderReceiver
{
  public:
  SenderReceiver(std::unique_ptr<Peripherals::Peripherals_generator> preipherals, PubSubClient& client);
  void publish();
  std::function<void(const char*, byte*, unsigned int)> get_callback();

  private:
  Logger m_logger; ///< serial logger
  std::unique_ptr<Peripherals::Peripherals_generator> m_peripherals; ///< peripherals inputs/outputs
  PubSubClient& m_client; ///< MQTT client

  void callback(const char* topic, byte* payload, unsigned int length);
};