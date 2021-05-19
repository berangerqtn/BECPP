#include "MyWebServer.h"
//IMPORTANT : Pour passer de mon code sur moniteur série à du test sur ESP GrooveShield
// Faire Ctrl+H dans le menu.h pour remplacer tous les Serial.println par lcd.print

rgb_lcd lcd;

void setup() {
  setup_ESP();
  setup_WebServer();
  main_menu.menu_init();
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
    Serial.println("Appuyez");
  }

  if (WiFi.isConnected()){
    digitalWrite(PIN_LED_WIFI_CONNECTED, HIGH);
    main_menu.computeGrams();
    updateList();
    WebServer.handleClient(); 
    
  } else {
    digitalWrite(PIN_LED_WIFI_CONNECTED, LOW);
    Serial.println("non connecté");
  }

}
