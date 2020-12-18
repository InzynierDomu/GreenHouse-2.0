#ifndef SENDERRECEIVER
#define SENDERRECEIVER

#include <Arduino.h>

#include "Peripherals/Peripherals_generator.h"

class Logger;

class SenderReceiver
{
public:
  SenderReceiver(Peripherals::Peripherals_generator* preipherals);
  void publish();
  std::function<void(const char*, byte*, unsigned int)> get_callback();

private:
  Logger* m_logger;
  Peripherals::Peripherals_generator* m_preipherals;

  void callback(const char* topic, byte* payload, unsigned int length);
};

#endif // SENDERRECEIVER