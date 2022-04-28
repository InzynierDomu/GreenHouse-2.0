#include "Screen.h"

namespace HAL
{

Screen::Screen()
{
  Adafruit_SSD1306 display(Config::screen_width, Config::screen_height, &Wire);
  display.begin(SSD1306_SWITCHCAPVCC, Config::screen_adress);

  display.clearDisplay();
  display.setRotation(2);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("GreenHouse 2.0");

  display.display();
}

void Screen::Print(String text)
{
  // display.clearDisplay();
  // display.setCursor(0, 0);
  // display.println(text);
  // display.display();
}

} // namespace HAL