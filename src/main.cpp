#include "MyWebServer.h"
//IMPORTANT : Pour passer de mon code sur moniteur série à du test sur ESP GrooveShield
// Faire Ctrl+H dans le menu.h pour remplacer tous les Serial.println par lcd.print

rgb_lcd lcd;
  
expert* Michel = new expert('m','m',300,1.9,'h');
young* Johnathane = new young('j','j',50,1.9,'f');

void setup() {
  setup_ESP();
  setup_WebServer();
  main_menu.menu_init();
  Michel->addConso();
  Johnathane->addConso();
  main_menu.addToList(Michel);
  main_menu.addToList(Johnathane);
  /*main_menu.addPlayer(user1);
  main_menu.addPlayer(user2);
  main_menu.addPlayer(user3);
  main_menu.addPlayer(user4);
  user1.set_actual_grams(1.2);
  user2.addConso();
  //user2.addConso();
  user3.addConso();
  user4.set_actual_grams(100);*/

}

void loop() {
  main_menu.computeGrams();
  updateList();
  if (digitalRead(Push)==1 && main_menu.get_m_level()==0){
    delay(300);
    main_menu.menu_display();
  } 
  else if (main_menu.get_m_level()==1){
    main_menu.menu_display();
  }
  else if (main_menu.get_m_level()==2){
    main_menu.menu_display();
  }
  // put your main code here, to run repeatedly:
  /*if (WiFi.isConnected()){
    digitalWrite(PIN_LED_WIFI_CONNECTED, HIGH);
    //Serial.println("connecté");
    //Serial.println("IP : ");
    //Serial.println(WiFi.localIP());
    main_menu.computeGrams();
    updateList();
    WebServer.handleClient(); //prend en charge les clients qui peuvent venir sur mon serveur
    
  } else {
    digitalWrite(PIN_LED_WIFI_CONNECTED, LOW);
    Serial.println("non connecté");
  }*/
  //WebServer.on("/afficher_liste", afficherListe);
   // WebServer.handleClient();
   //computeGrams();

}