/**
 * @file Network.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief WiFi and MQTT handling
 * @date 2022-06
 */
#pragma once

#include "Logger.h"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ESP32
#include <WiFi.h>
#endif
#include <PubSubClient.h>
#include <time.h>

namespace HAL
{

struct Mqtt_config
{
  Mqtt_config(const char* _address, const char* _user, const char* _id, const char* _pass)
  : address(_address)
  , user(_user)
  , id(_id)
  , pass(_pass)
  {}
  const char* address;
  const char* user;
  const char* id;
  const char* pass;
};

class Network
{
  public:
  Network(const char* ssid, const char* pass, const Mqtt_config mqtt_config);
  PubSubClient& get_mqtt_client();
  void mqtt_reconnect(const char* topic);
  void set_mqtt_callback(std::function<void(const char*, byte*, unsigned int)> callback);
  void loop();

  private:
  Logger m_logger;  ///< logger
  WiFiClient m_espClient; ///< WiFi handling 
  std::unique_ptr<PubSubClient> m_mqtt_client;  ///< mqtt handling
  const Mqtt_config m_mqtt_config;  ///< mqtt configuration

  void connect_wifi(const char* ssid, const char* pass);
};
} // namespace HAL