#ifndef HAL_WIFI
#define HAL_WIFI

#include "Logger.h"

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <time.h>

namespace HAL
{

class Wifi
{
  public:
  Wifi(const char* ssid, const char* pass, const char* mqtt_addres);
  PubSubClient& get_mqtt_client();
  void mqtt_reconnect(const char* topic);
  void set_mqtt_callback(std::function<void(const char*, byte*, unsigned int)> callback);
  void loop();

  private:
  Logger m_logger;
  WiFiClient m_espClient;
  std::unique_ptr<PubSubClient> m_mqtt_client;

  void connect_wifi(const char* ssid, const char* pass);
};
} // namespace HAL

#endif // HAL_WIFI