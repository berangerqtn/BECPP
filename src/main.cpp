#include "MyWebServer.h"
#include "Arduino.h"
#include "rgb_lcd.h"
#include "user.h"
#include "user_list.h"
#include "beer_tappping.h"


user * main_user = new user;
user_list user_list1;

void setup() {
  // put your setup code here, to run once:
  setup_ESP();
  setup_WebServer();
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.begin(9600);
  user_list1.add_user(main_user);
  main_user->set_info();
  
  user_list1.print_list();
}

void loop(){
  // put your main code here, to run repeatedly:
  if (WiFi.isConnected()){
    WebServer.handleClient();
  }
    
}
