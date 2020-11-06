#include "Init.h"
#include "Bme_sensor.h"
#include "Keyboard.h"
#include "Screen.h"
#include "GPIO_controller.h"

namespace HAL{

Init::Init()
{
  scan_i2c();

  m_keyboard = new Keyboard(Config::m_keyboard_pcf_adress);
  m_screen = new Screen();  
  m_bme_sensor = new Bme_sensor();
  generate_gpio_controllers();
}

Bme_sensor* Init::get_bme_sensor()
{
  return m_bme_sensor;
}

GPIO_controller* Init::get_GPIO_controller(int adress)
{
}

void Init::scan_i2c()
{
  Wire.begin();
  for(int address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();
    if (error == 0)
    {
      m_i2c_adress.push_back(address);
      Serial.print("I2C device found at address");
      Serial.println(address);
    }
  }
}

void Init::generate_gpio_controllers()
{
    for(auto it = m_i2c_adress.begin(); it != m_i2c_adress.end(); ++it)
    {
      if(*it > min_adress_gpio_controllers && *it <= max_adress_gpio_controllers)
      {
        GPIO_controller *gpio_controller = new GPIO_controller();
        m_gpio_controllers.push_back(*gpio_controller);
      }
    }
}

} //namespace HAL