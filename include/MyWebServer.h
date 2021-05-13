#ifndef MYWEBSERVER_H
#define MYWEBSERVER_H

#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "menu.h"
#include "user.h"
#include <string>
#include <iostream>

#define PIN_LED_WIFI_CONNECTED 15

//using namespace std;

//source info alcool : https://www.stagespointspermis.fr/656-l-points-de-permis-temps-elimination-alcool.html

//Creation of WebServer object
ESP8266WebServer WebServer(80);

//Network ID
/*const char* SSID ="DJZier";
const char* MDP ="flolpb64";*/

const char* SSID ="Livebox-C4A6";
const char* MDP ="lulukiki";

menu main_menu;
list<user*> myList = main_menu.get_list();
int i = 1;


//LED to drive
int LED_STATE=0;

void setup_ESP();
void setup_WebServer();
void root();
void updateList();
void LED_ON();
void LED_OFF();
void onGotIP(const WiFiEventStationModeGotIP event);
void onConnected(const WiFiEventStationModeConnected event);
void computeGrams();



const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="fr">
    <head>
        <meta charset="UTF-8">
        <title>LED Driver</title>
    </head>
    <body>
        <h1>State of the LED</h1>
        <h2>%LED%</h2>
        <h2>%personne 1%</h2>
        <h2>%personne 2%</h2>
        <h2>%personne 3%</h2>
        <h2>%personne 4%</h2>

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

String temp(reinterpret_cast<const __FlashStringHelper *>(index_html));


void setup_ESP(){
      // put your setup code here, to run once:
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.begin(9600);
  Serial.println("");
  pinMode(5,INPUT);  
  pinMode(16,OUTPUT);  
  pinMode(PIN_LED_WIFI_CONNECTED, OUTPUT);
  LED_OFF();
  

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
  WebServer.on("/afficher_liste", updateList);
  WebServer.on("/",root);
  WebServer.begin();

}

void updateList(){
  myList = main_menu.get_list();
  list<user*>::iterator it ;
  String texte_remp;
  String toReplace;
  computeGrams();
  for (it = myList.begin(); it!= myList.end(); it++){
    toReplace = "%personne " + (String)i +"%";
    texte_remp = (String)(*it)->get_i0() + " " + (String)(*it)->get_i1() + " actual grams :" + (String)(*it)->get_actual_grams();
    temp.replace(toReplace, texte_remp);
    i=i+1;
  }
  i=1; 
  WebServer.send(200, "text/html",temp);
}


void LED_ON(){
  digitalWrite(16,HIGH);
  //WebServer.send(200, "text/html", "Led On");
  LED_STATE=1;
  root();
}
void LED_OFF(){
  digitalWrite(16,LOW);
  //WebServer.send(200, "text/html", "Led Off");
  LED_STATE=0;
  root();
}

void root(){
  if (digitalRead(16)==HIGH){
    temp.replace("%LED%","LED ON");
  }
    
  else{
    temp.replace("%LED%","LED OFF");
  }
    

  WebServer.send(200, "text/html",temp);
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



void computeGrams(){
  list<user*>::iterator it ;
  myList = main_menu.get_list();
  for (it = myList.begin(); it!= myList.end(); it++){
    if ((*it)->get_sexe() == 'f'){
      //(*it)->set_actual_grams((*it)->get_actual_grams()-0.085*(millis()-(*it)->get_time())/3600000);
      (*it)->set_actual_grams((*it)->get_actual_grams()+0.01);
    }
    else if ((*it)->get_sexe() == 'h'){
      (*it)->set_actual_grams((*it)->get_actual_grams()-(0.1*(millis()-(*it)->get_time())/3600000));
    }
    
    (*it)->set_time(millis());
  }
}

#endif //MYWEBSERVER_H