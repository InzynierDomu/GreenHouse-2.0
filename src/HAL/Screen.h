#pragma once

#include "Config.h"

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

namespace HAL
{
class Screen
{
  public:
  Screen();
  void print(String text);
  private:
  Adafruit_SSD1306 m_display;
};
} // namespace HAL
