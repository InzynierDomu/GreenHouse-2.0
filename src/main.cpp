/**
 * @file Main.cpp
 * @brief GreenHouse 2.0 - Main
 * @author Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */

#include "HAL/Init.h"
#include "HAL/Real_clock.h"
#include "HAL/Screen.h"
#include "Liner_fun.h"
#include "Logger.h"
#include "Peripherals/Peripherals_generator.h"
#include "Scheduler.h"
#include "SenderReceiver.h"
#include "Supervisor.h"

#include <Arduino.h>
#include <ArduinoJson.h>
#include <memory>

Logger m_logger("Main", HAL::Real_clock::get_instance()->get_time_callback());
Supervisor m_supervisor;
HAL::Init* m_hal;
std::unique_ptr<Peripherals::Peripherals_generator> m_peripherals;
std::unique_ptr<SenderReceiver> m_sender_reciver;
std::unique_ptr<Scheduler> m_scheduler;

StaticJsonDocument<2048> doc;

enum class Setup_state
{
  hal_init,
  json_deserialize,
  network_init,
  generation_peripherals,
  connect_sender_reciver,
  setup_finished
};

void setup()
{
  Setup_state state = Setup_state::hal_init;
  Serial.begin(115200);
  m_logger.log("Start setup");
  m_supervisor = Supervisor();
  while (m_supervisor.get_state() == Device_state::ok && state != Setup_state::setup_finished)
  {
    switch (state)
    {
      case Setup_state::hal_init:
        m_hal = new HAL::Init(m_supervisor);
        m_hal->get_screen()->print("Startup");
        state = Setup_state::json_deserialize;
        break;
      case Setup_state::json_deserialize:
        m_hal->deserializeConfigJson(doc);
        state = Setup_state::network_init;
        break;
      case Setup_state::network_init:
        m_hal->initNetwork(doc);
        state = Setup_state::generation_peripherals;
        break;
      case Setup_state::generation_peripherals:
        m_scheduler = std::make_unique<Scheduler>();
        m_peripherals = std::make_unique<Peripherals::Peripherals_generator>(m_hal, doc, m_hal->get_wifi_mqtt_client(), m_scheduler.get());
        state = Setup_state::connect_sender_reciver;
        break;
      case Setup_state::connect_sender_reciver:
        m_sender_reciver = std::make_unique<SenderReceiver>(std::move(m_peripherals), m_hal->get_wifi_mqtt_client());
        m_hal->set_mqtt_callback(m_sender_reciver->get_callback());
        state = Setup_state::setup_finished;
        break;
    }
  }
  m_logger.log("Setup finished");
  m_hal->get_screen()->print("Geenhouse 2.0");
}

void loop()
{
  if (m_supervisor.get_state() == Device_state::ok)
  {
    // todo: add check i2c
    m_hal->wifi_mqtt_reconnect();
    m_hal->mqtt_loop();

    static long last_loop_time = 0;
    long loop_time = millis();
    m_scheduler->check_events(loop_time);
    if (loop_time - last_loop_time > 60000)
    {
      m_sender_reciver->publish();
      last_loop_time = millis();
    }

    // error if loop > 1s turn off evrything
  }
  else
  {
    m_hal->get_screen()->print("error");
    delay(500);
  }
}
