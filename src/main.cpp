#include <Arduino.h>
#include <ArduinoJson.h>

#include "Logger.h"
#include "HAL/Init.h"
#include "Peripherals/Peripherals_generator.h"
#include "SenderReceiver.h"
#include "test_json.h"
#include "Liner_fun.h"

Logger* m_logger;
HAL::Init *m_hal;
Peripherals::Peripherals_generator *m_peripherals;
SenderReceiver* m_sender_reciver;

StaticJsonDocument<800> doc;

void setup() 
{
  Serial.begin(9600);
  m_logger = new Logger("Main");
  m_logger->log("Start setup");

  String deserialization_state = deserializeJson(doc, test_json::content).c_str();
  if(!deserialization_state.compareTo("Ok"))
  {
    m_logger->log("Deserialization Ok");
  }
  else
  {
    m_logger->log("Deserialization " + deserialization_state, Msg_type::warning);
  }

  m_hal = new HAL::Init(doc);

  m_peripherals = new Peripherals::Peripherals_generator(m_hal, doc, m_hal->get_wifi_mqtt_client());

  m_sender_reciver = new SenderReceiver(m_peripherals);
  m_hal->set_mqtt_callback(m_sender_reciver->get_callback());

  m_logger->log("Finish setup");
}

void loop() 
{ 
  m_hal->wifi_mqtt_reconnect();
  m_hal->mqtt_loop();

  m_peripherals->publish();

  delay(1000);
}