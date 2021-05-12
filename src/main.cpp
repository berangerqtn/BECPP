#include "MyWebServer.h"
#include "menu.h"

// A toi de modifier Flo !
//menu main_menu;
user user1('f','c',80,1.75);
user user2('b','q',90,1.90);
user user3('s','g',60,1.54);
user user4('g','d',120,1.85);
//user user5('b','l',70,1.86);


void setup() {
  setup_ESP();
  setup_WebServer();  
  main_menu.addPlayer(user1);
  main_menu.addPlayer(user2);
  main_menu.addPlayer(user3);
  main_menu.addPlayer(user4);
}

void loop() {

  //main_menu.menu_display();
  // put your main code here, to run repeatedly:
  if (WiFi.isConnected()){
    digitalWrite(PIN_LED_WIFI_CONNECTED, HIGH);
    Serial.println("connecté");
    Serial.println("IP : ");
    Serial.println(WiFi.localIP());
    WebServer.handleClient(); //prend en charge les clients qui peuvent venir sur mon serveur
  } else {
    digitalWrite(PIN_LED_WIFI_CONNECTED, LOW);
    Serial.println("non connecté");
  }
  
   // WebServer.handleClient();

}