#include "Init.h"
#include "Keyboard.h"
#include "Screen.h"
#include "GPIO_controller.h"

namespace HAL{

Init::Init()
{
  m_keyboard = new Keyboard(Config::m_keyboard_pcf_adress);
  m_screen = new Screen();  
  Bme_init();
}

void Init::set_keyoboard_buttons(bool *is_pressed, Keyboard_button *button)
{
    
}

float Init::get_bme_temp()
{
  return m_bme_sensor.readTemperature();
}

float Init::get_bme_hum()
{
  return m_bme_sensor.readHumidity();
}
    
void Init::Bme_init()
{
  if(!m_bme_sensor.begin(BME280_ADDRESS_ALTERNATE))
  {
    Serial.println("bme280 init failed");
  }
}

} //namespace HAL