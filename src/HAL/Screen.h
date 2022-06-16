/**
 * @file Screen.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Screen handling
 * @date 2022-06
 */

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
  void print(const String& text);

  private:
  Adafruit_SSD1306 m_display; ///< SSD1306
};
} // namespace HAL
