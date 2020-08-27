#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "HAL/Keyboard.h"
#include "test_json.h"
#include "pin_config.h"
#include "Liner_fun.h"

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1// Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//TODO: move to some config file
const byte m_keyboard_pcf_adress = 0x20;

WiFiClient espClient;
PubSubClient client(espClient);

StaticJsonDocument<200> doc;

bool volatile m_keyboatd_button_presed;

HAL::Keyboard keyboard(m_keyboard_pcf_adress);

Linear_function test_f;

void ICACHE_RAM_ATTR readpcf()
{
  m_keyboatd_button_presed = true;
}

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

  DeserializationError error = deserializeJson(doc, test_json::content);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
  }
  else
  {
    Serial.println(F("SSD1306 allocation ok"));
  } 

  display.clearDisplay();
  display.setRotation(2);
  display.setTextSize(2);      
  display.setTextColor(SSD1306_WHITE); 
  // display.setTextColor(BLACK, WHITE);  
  display.display();

  pinMode(pins::m_keyboard_int, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pins::m_keyboard_int), readpcf, FALLING);

  //TODO: move to read from memory
  Point ph4(4, 95);
  Point ph7(7, 365);

  test_f = calculate(ph4, ph7);  

  setup_wifi(doc["SSID"],doc["PASS"]);
  client.setServer("192.168.0.17", 1883);
}

void loop() { 
  if (!client.connected()) 
  {
    reconnect(doc["MQTT_TOPIC_TEST"]);
  }
  if (m_keyboatd_button_presed)
  {
    keyboard.keyboard_action();
    m_keyboatd_button_presed = false;
  }

  int analog_ph = analogRead(pins::m_analog);

  display.clearDisplay();
  display.setCursor(0, 0);   
  display.print(find_y(analog_ph, test_f));
  display.println("pH");
  // display.println("uS/cm");
  display.display();
}