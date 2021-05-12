#include "MyWebServer.h"
#include "menu.h"
//IMPORTANT : Pour passer de mon code sur moniteur série à du test sur ESP GrooveShield
// Faire Ctrl+H dans le menu.h pour remplacer tous les Serial.println par lcd.print

rgb_lcd lcd;
menu main_menu;  


void setup() {
  setup_ESP();
  setup_WebServer();
  main_menu.menu_init();
  expert newUser('F', 'U', 193, 1.45);
  main_menu.add_to_list(newUser);

}

void loop() {
  main_menu.menu_display(); 
  // put your main code here, to run repeatedly:
  //if (WiFi.isConnected())
   // WebServer.handleClient();

}