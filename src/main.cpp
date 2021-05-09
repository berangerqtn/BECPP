#include "MyWebServer.h"
#include "menu.h"

// A toi de modifier Flo !
menu main_menu;

void setup() {
  setup_ESP();
  setup_WebServer();  
}

void loop() {

  main_menu.menu_display();
  // put your main code here, to run repeatedly:
  //if (WiFi.isConnected())
   // WebServer.handleClient();

}