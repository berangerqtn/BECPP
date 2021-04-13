//#include "MyWebServer.h"
#include "Arduino.h"
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
  // put your setup code here, to run once:
  //setup_ESP();
  //setup_WebServer();
  //digitalWrite(LED_BUILTIN,HIGH);

  //LCD
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {

  if (Serial.available()){
    lcd.clear();
    lcd.print("Hello Beauté");
  }
  // put your main code here, to run repeatedly:
  //if (WiFi.isConnected())
    //WebServer.handleClient();
  //touchButton();
}