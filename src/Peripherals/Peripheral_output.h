#pragma once

namespace Peripherals
{

class Peripheral_output
{
  public:
  virtual ~Peripheral_output() {}
  virtual void set_value(const uint8_t value) = 0;
  virtual String get_topic() const = 0;
};

} // namespace Peripherals