#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "HAL/Keyboard.h"
#include "test_json.h"

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1// Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//TODO: move to some config file
const byte m_pin_analog = A0;
const byte m_pin_keyboard_int = D5;
const byte m_keyboard_pcf_adress = 0x20;

bool volatile m_keyboatd_button_presed;

void ICACHE_RAM_ATTR readpcf()
{
  m_keyboatd_button_presed = true;
}

HAL::Keyboard keyboard(m_keyboard_pcf_adress);

struct Linear_function
{
  //y = ax + b
  double a;
  double b; 
};

struct Point
{
  Point(int _y, int _x):y(_y), x(_x){};
  int y;
  int x;
};

Linear_function calculate(Point first, Point second)
{
  Linear_function f;
  f.a = (second.y - first.y)/(double)(second.x - first.x);
  f.b = first.y - (f.a * first.x);
  return f;
}

double find_y(int x, Linear_function f)
{
  return(f.a * x + f.b);
}

Linear_function test_f;

void setup() {
  Serial.begin(9600);
  
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

  pinMode(D5, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(m_pin_keyboard_int), readpcf, FALLING);

  //TODO: move to read from memory
  Point ph4(4, 95);
  Point ph7(7, 365);

  test_f = calculate(ph4, ph7);  
}

void loop() { 
  if (m_keyboatd_button_presed)
  {
    keyboard.keyboard_action();
    m_keyboatd_button_presed = false;
  }

  int analog_ph = analogRead(m_pin_analog);

  display.clearDisplay();
  display.setCursor(0, 0);   
  display.print(find_y(analog_ph, test_f));
  display.println("pH");
  // display.println("uS/cm");
  display.display();
}