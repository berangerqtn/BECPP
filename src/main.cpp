#include "MyWebServer.h"
//IMPORTANT : Pour passer de mon code sur moniteur série à du test sur ESP GrooveShield
// Faire Ctrl+H dans le menu.h pour remplacer tous les Serial.println par lcd.print

rgb_lcd lcd;
  
expert* Michel = new expert('m','m',300,1.9,'h');
young* Johnathane = new young('j','j',50,1.9,'f');
expert* Michelle = new expert('m','m',300,1.9,'h');
young* Johnathan = new young('j','j',50,1.9,'f');
expert* Michellle = new expert('m','m',300,1.9,'h');



void setup() {
  setup_ESP();
  setup_WebServer();
  main_menu.menu_init();
  Michel->addConso();
  Johnathane->addConso();
  main_menu.addToList(Michel);
  main_menu.addToList(Johnathane);
  main_menu.addToList(Michelle);
  main_menu.addToList(Johnathan);
  main_menu.addToList(Michellle);
}

void loop() {
  main_menu.computeGrams();
  updateList();
  if (digitalRead(Push)==1 && main_menu.get_m_level()==0){
    delay(300);
    standby=false;
    main_menu.menu_display();
  } 
  else if (main_menu.get_m_level()==1){
    main_menu.menu_display();
  }
  else if (main_menu.get_m_level()==2){
    main_menu.menu_display();
  }
  if (standby){
    lcd.clear();
    lcd.print("Appuyez");
  }

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
