#include "MyWebServer.h"
#include "menu.h"
//IMPORTANT : Pour passer de mon code sur moniteur série à du test sur ESP GrooveShield
// Faire Ctrl+H dans le menu.h pour remplacer tous les Serial.println par lcd.print

rgb_lcd lcd;

void setup() {
  setup_ESP();
  setup_WebServer();
  menu main_menu;  
  main_menu.menu_init();
  main_menu.menu_display();
}

void loop() {
  // put your main code here, to run repeatedly:
  //if (WiFi.isConnected())
   // WebServer.handleClient();

}