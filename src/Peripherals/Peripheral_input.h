#pragma once

#include <PubSubClient.h>

namespace Peripherals
{

class PubSubClien;

class Peripheral_input
{
  public:
  virtual ~Peripheral_input() {}
  virtual void publish(PubSubClient& client) = 0;
};

} // namespace Peripherals