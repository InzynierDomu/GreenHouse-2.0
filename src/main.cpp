/**
 * @file Main.cpp
 * @brief GreenHouse 2.0 - Main
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @date 01-2021
 */
#include "Config.h"
#include "HAL/Init.h"
#include "HAL/Real_clock.h"
#include "HAL/Screen.h"
#include "Logger.h"
#include "Peripherals/Peripherals.h"
#include "Peripherals/Peripherals_creator.h"
#include "Scheduler.h"
#include "SenderReceiver.h"
#include "Supervisor.h"

#include <Arduino.h>
#include <ArduinoJson.h>
#include <memory>

Logger m_logger("Main", HAL::Real_clock::get_instance()->get_time_callback());
Supervisor m_supervisor;
std::unique_ptr<HAL::Init> m_hal;
std::unique_ptr<Peripherals::Peripherals_creator> m_peripherals_creator;
std::unique_ptr<Peripherals::Peripherals> m_peripherals;
std::unique_ptr<SenderReceiver> m_sender_reciver;
Scheduler m_scheduler;

StaticJsonDocument<Config::max_json_size> doc;

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
  Serial.begin(Config::serial_baudrate);
  m_logger.log("Start setup");
  while (m_supervisor.get_state() == Device_state::ok && state != Setup_state::setup_finished)
  {
    switch (state)
    {
      case Setup_state::hal_init:
        m_hal = std::make_unique<HAL::Init>(m_supervisor);
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
        m_peripherals = std::make_unique<Peripherals::Peripherals>();
        m_peripherals_creator = std::make_unique<Peripherals::Peripherals_creator>(
            m_peripherals.get(), m_hal.get(), doc, m_hal->get_wifi_mqtt_client(), m_scheduler);
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
  m_hal->get_screen()->print("Greenhouse\nv:" + Config::sw_version);
}

void loop()
{
  if (m_supervisor.get_state() == Device_state::ok)
  {
    // todo: add check i2c
    m_hal->wifi_mqtt_reconnect();
    m_hal->mqtt_loop();

    static long last_loop_time = 0; // TODO: move to sender reciver
    long loop_time = millis();
    m_scheduler.check_events(loop_time);
    if (loop_time - last_loop_time > 60000)
    {
      m_sender_reciver->publish();
      last_loop_time = millis();
    }

    // TODO: error if loop > 1s, supervisor
  }
  else
  {
    m_hal->get_screen()->print("error");
    delay(500);
  }
}
