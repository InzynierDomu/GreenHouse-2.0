/**
 * @file Main.cpp
 * @brief GreenHouse 2.0 - Main
 * @author Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/  
 * @date 01-2021
 */

#include <Arduino.h>
#include <ArduinoJson.h>
#include <memory>

#include "Logger.h"
#include "HAL/Init.h"
#include "Peripherals/Peripherals_generator.h"
#include "SenderReceiver.h"
#include "Liner_fun.h"

Logger m_logger("Main");
HAL::Init *m_hal;
std::unique_ptr<Peripherals::Peripherals_generator> m_peripherals;
SenderReceiver* m_sender_reciver;

StaticJsonDocument<800> doc;

void setup() 
{
  Serial.begin(9600);
  m_logger.log("Start setup");

  m_hal = new HAL::Init();
  m_hal->deserializeConfigJson(doc);
  m_hal->initNetwork(doc);

  m_peripherals = std::make_unique<Peripherals::Peripherals_generator>(m_hal, doc, m_hal->get_wifi_mqtt_client());

  m_sender_reciver = new SenderReceiver(std::move(m_peripherals), m_hal->get_wifi_mqtt_client());
  m_hal->set_mqtt_callback(m_sender_reciver->get_callback());

  m_logger.log("Setup finished");
}

void loop() 
{ 
  m_hal->wifi_mqtt_reconnect();
  m_hal->mqtt_loop();

  static long last_loop_time = 0;
  long loop_time = millis();
  if(loop_time - last_loop_time > 60000)
  {
    m_sender_reciver->publish();
    last_loop_time = millis();
  }
}