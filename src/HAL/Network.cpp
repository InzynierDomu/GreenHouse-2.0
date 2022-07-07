/**
 * @file Network.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief WiFi and MQTT handling
 * @date 2022-06
 */
#include "Network.h"

#include "Config.h"
#include "Real_clock.h"

namespace HAL
{

/**
 * @brief Construct a new Network:: Network object
 * @param ssid: WiFi ssid
 * @param pass: WiFi pass
 * @param mqtt_config: mqtt configuration
 */
Network::Network(const char* ssid, const char* pass, const Mqtt_config mqtt_config)
: m_logger(Logger("WiFi", Real_clock::get_instance()->get_time_callback()))
, m_mqtt_config(mqtt_config) // TODO: posible better move
{
  connect_wifi(ssid, pass);

  m_mqtt_client = std::make_unique<PubSubClient>(m_espClient);
  m_mqtt_client->setServer(m_mqtt_config.address, Config::mqtt_port);
}

/**
 * @brief get mqtt client
 * @return mqtt client
 */
PubSubClient& Network::get_mqtt_client()
{
  return *m_mqtt_client;
}

/**
 * @brief reconnect mqtt subscription
 * @param topic: subscribing topic
 */
void Network::mqtt_reconnect(const char* topic)
{
  while (!m_mqtt_client->connected())
  {
    m_logger.log("Attempting MQTT connection");
    if (m_mqtt_client->connect(m_mqtt_config.id, m_mqtt_config.user, m_mqtt_config.pass))
    {
      m_logger.log("Connected");
      m_mqtt_client->subscribe(topic);
    }
    else
    {
      m_logger.log("Failed, rc=" + String(m_mqtt_client->state()), Log_type::warning);
      m_logger.log("Try again in 5 seconds");
      delay(5000);
    }
  }
}

/**
 * @brief set callback for recive mqtt message
 * @param callback: callback
 */
void Network::set_mqtt_callback(std::function<void(const char*, byte*, unsigned int)> callback)
{
  m_mqtt_client->setCallback(callback);
}

/**
 * @brief main mqtt check loop
 */
void Network::loop()
{
  m_mqtt_client->loop();
}

void Network::connect_wifi(const char* ssid, const char* pass)
{
  m_logger.log("Connecting to " + String(ssid));

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    m_logger.log(".");
  }

  m_logger.log("Connected");
  auto address = WiFi.localIP();
  m_logger.log("IP address: " + String(address[0]) + ":" + String(address[1]) + ":" + String(address[2]) + ":" + String(address[3]));
}

} // namespace HAL
