#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "HAL/Init.h"
#include "test_json.h"
#include "Liner_fun.h"

HAL::Init *m_hal;

WiFiClient espClient;
PubSubClient client(espClient);

StaticJsonDocument<400> doc;

Linear_function test_f;

//TODO: wywalic!!!!

void setup_wifi(const char* ssid, const char* pass) 
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect(const char* topic) 
{
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

//--------------------------------------------------------------------

void setup() {
  Serial.begin(9600);

  m_hal = new HAL::Init();

  DeserializationError error = deserializeJson(doc, test_json::content);
  Serial.println(error.c_str());
  String topic_test = doc["HARDWARE_CONFIGURATION"]["GPIO_CONTROLLERS"][0]["GPIOS"][0]["TOPIC"];
  Serial.println(topic_test);

  //TODO: move to read from memory
  Point ph4(4, 95);
  Point ph7(7, 365);

  test_f = calculate(ph4, ph7);  

  // setup_wifi(doc["SSID"],doc["PASS"]);
  // client.setServer("192.168.0.17", 1883);
}

void loop() { 
  // if (!client.connected()) 
  // {
  //   reconnect(doc["MQTT_TOPIC_TEST"]);
  // }

  // if (m_keyboatd_button_presed)
  // {
  //   keyboard.keyboard_action();
  //   m_keyboatd_button_presed = false;
  // }

  int analog_ph = 100; // analogRead(pins::m_analog);

  // display.clearDisplay();
  // display.setCursor(0, 0);   
  // display.print(find_y(analog_ph, test_f));
  // display.println("pH");
  // // display.println("uS/cm");
  // display.display();
}