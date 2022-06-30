#include "Screen.h"

namespace HAL
{

/**
 * @brief Construct a new Screen:: Screen object
 */
Screen::Screen()
: m_display(Config::screen_width, Config::screen_height, &Wire)
{
  m_display.begin(SSD1306_SWITCHCAPVCC, Config::screen_address);

  m_display.clearDisplay();
  m_display.setRotation(0);
  m_display.setTextSize(2);
  m_display.setTextColor(SSD1306_WHITE);
}

/**
 * @brief print text on screen
 * @param text: text to print
 */
void Screen::print(const String& text)
{
  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.println(text);
  m_display.display();
}

} // namespace HAL