#include "WiFi.h"

#include "config.h"


namespace HAL
{

Wifi::Wifi(const char* ssid, const char* pass, const char* mqtt_addres)
: m_logger(Logger("WiFi"))
{
  connect_wifi(ssid, pass);

  m_mqtt_client = new PubSubClient(m_espClient);
  m_mqtt_client->setServer(mqtt_addres, Config::mqtt_port);
}

PubSubClient* Wifi::get_mqtt_client()
{
  return m_mqtt_client;
}

void Wifi::mqtt_reconnect(const char* topic)
{
  while (!m_mqtt_client->connected())
  {
    m_logger.log("Attempting MQTT connection");
    if (m_mqtt_client->connect("123", "id", "id"))
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

void Wifi::set_mqtt_callback(std::function<void(const char*, byte*, unsigned int)> callback)
{
  m_mqtt_client->setCallback(callback);
}

void Wifi::loop()
{
  m_mqtt_client->loop();
}

void Wifi::connect_wifi(const char* ssid, const char* pass)
{
  m_logger.log("Connecting");

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  m_logger.log("Connected");
  m_logger.log("IP address:" + WiFi.localIP());
}

} // namespace HAL
