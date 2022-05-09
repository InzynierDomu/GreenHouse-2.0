#pragma once

namespace Peripherals
{

class Peripheral
{
  public:
  virtual ~Peripheral() {}

  protected:
  String m_topic;
  int m_pin;
};

} // namespace Peripherals