#ifndef MYWEBSERVER_H
#define MYWEBSERVER_H

#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"



//Creation of WebServer object
ESP8266WebServer WebServer(80);

//Network ID
const char* SSID ="OPPO A72";
const char* MDP ="berangerqtn";

//LED to drive
int LED_STATE=0;

void setup_ESP();
void setup_WebServer();
void root();
void LED_ON();
void LED_OFF();
void onGotIP(const WiFiEventStationModeGotIP event);
void onConnected(const WiFiEventStationModeConnected event);
void touchButton();

const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="fr">
    <head>
        <meta charset="UTF-8">
        <title>LED Driver</title>
    </head>
    <body>
        <h1>State of the LED</h1>
        <h2>Unknown</h2>
        <h1>LED Driver</h1>
        <a href="/LED_ON">
        <button>Turn the LED ON</button>
        </a>
        <a href="/LED_OFF">
        <button>Turn the LED OFF</button>
        </a>
    </body>
</html>
)=====";




void setup_ESP(){
      // put your setup code here, to run once:
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.begin(9600);
  Serial.println("");
  pinMode(5,INPUT);  
}

void setup_WebServer(){
//Mode de Connexion : Station 
  WiFi.mode(WIFI_STA);
  //Démarrage de connexion Wifi
  WiFi.begin(SSID,MDP);

  static WiFiEventHandler onConnectedHandler = WiFi.onStationModeConnected(onConnected);
  static WiFiEventHandler onGotIPHandler = WiFi.onStationModeGotIP(onGotIP);

  //Mise en place du Serveur Web
  WebServer.on("/LED_ON", LED_ON);
  WebServer.on("/LED_OFF", LED_OFF);
  WebServer.on("/",root);
  WebServer.begin();

}

void LED_ON(){
  digitalWrite(16,HIGH);
  LED_STATE=1;
  root();
}
void LED_OFF(){
  digitalWrite(16,LOW);
  LED_STATE=0;
  root();
}

void root(){
  String temp(reinterpret_cast<const __FlashStringHelper *>(index_html));
  if (digitalRead(16)==HIGH)
    temp.replace("%LED%","LED ON");
  else
    temp.replace("%LED%","LED OFF");

  WebServer.send(200, "text/html",index_html);
}

void onConnected(const WiFiEventStationModeConnected event){
  Serial.println("Connected to WiFi Network");
}

void onGotIP(const WiFiEventStationModeGotIP event){
    Serial.println("IP : ");
    Serial.println(WiFi.localIP());
    Serial.println("Network Speed :");
    Serial.println(WiFi.RSSI());
}

void touchButton(){
  if (digitalRead(0)==HIGH)
    Serial.println("You pushed");
    delay(200);
}

#endif //MYWEBSERVER_H