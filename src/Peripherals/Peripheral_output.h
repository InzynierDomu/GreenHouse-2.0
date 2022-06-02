#pragma once

namespace Peripherals
{

class Peripheral_output
{
  public:
  virtual ~Peripheral_output() {}
  virtual void set_value(uint8_t value) = 0;
};

} // namespace Peripherals