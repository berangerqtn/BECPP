#include "MyWebServer.h"
#include "Arduino.h"
#include "rgb_lcd.h"
#include "user.h"
#include "beer_tappping.h"

void setup() {
  // put your setup code here, to run once:
  setup_ESP();
  setup_WebServer();
  digitalWrite(LED_BUILTIN,HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.isConnected())
    WebServer.handleClient();
  touchButton();
}