#ifndef MENU_H
#define MENU_H

#include <map>
#include <list>
#include "rgb_lcd.h"

#include "user.h"

uint8_t ligne = 2;
bool standby = true; // 1 = Veille :: 0 = LCD en marche 


class menu{
    
protected :
    std::map<int,String> m0; //Premier niveau de menu
    std::map<int,String> m1; //Sous menu de Consommation
    list<user*> l_user;
    list<user*>::iterator it;

    int m_level;

public :
    void menu_display();
    char set_i0();
    char set_i1();
    int set_weight();
    float set_height();
    rgb_lcd lcd;

    char set_sexe();
    list<user*> get_list(){return l_user;}
    /*void addPlayer(user& u);
    void addPlayer(young& u);
    void addPlayer(expert& u);*/
    void addPlayer(int user_type);
    void computeGrams();
    int get_m_level(){return m_level;};
    void addToList(user*newU);
    menu();
    void menu_init();

};

menu main_menu;
list<user*> myList = main_menu.get_list();


menu::menu(){
    m0[0]= "Ajouter un joueur";
    m0[1]="Voir Utilisateurs";
    m0[2]="Consommer";
    m0[3]="Retour";

    m1[0]="Selection Utilisateur";
    m1[1]="Retour";
    m_level=0;
}


void menu::menu_display(){
    
    if (m_level==0){        
        while(digitalRead(Push)!=HIGH){
            lcd.clear();
            yield();
            computeGrams();
            if (analogRead(Pot)<1024/4){
                lcd.clear();
                Serial.println(m0[0]);
                delay(200);
            }
            else if (1024/4<analogRead(Pot) && analogRead(Pot)<1024*2/4){
                lcd.clear();
                Serial.println(m0[1]);
                delay(200);
            }
            else if (1024*2/4<analogRead(Pot) && analogRead(Pot)<1024*3/4) {
                lcd.clear();
                Serial.println(m0[2]);
                delay(200);
            }
            else{
                lcd.clear();
                Serial.println(m0[3]);
                delay(100);
            }
        }
        delay(200);

        if (analogRead(0)<1024/4){
            //ADD USERS
            //Serial.println("Quel ??ge avez vous ?");
            lcd.clear();
            Serial.println("Quel age avez vous ?");
            delay(1000);
            lcd.setCursor(1,0);
            while (digitalRead(Push)!=HIGH){
                lcd.clear();
                Serial.println(18+analogRead(Pot)/13);
                //Serial.println(18+analogRead(Pot)/13);
                delay(100);
                computeGrams();
                yield();
            }
            delay(200);

            try{
                if (l_user.size()>4)
                    throw 1;
                else{
                    if (18+analogRead(Pot)/13<22){
                        main_menu.addPlayer(2); // Cr??ation d'un jeune conducteur
                        m_level=0;
                    }
                    else{
                        main_menu.addPlayer(1); // Cr??ation d'un vieux conducteur
                        m_level=0;
                    }
                }
            }
            catch(int n){
                lcd.clear();
                lcd.setCursor(0,0);
                Serial.println("COVIDpas+de6");
                delay(2000);
            }  
            standby=true;
            
        }

        //SEE USERS

        else if (1024/4<analogRead(0) && analogRead(0)<1024*2/4){
            lcd.clear();
            it=l_user.begin();
            while (it!=l_user.end()){
                //Serial.print((*it).get_i0()+(*it).get_i1()+" grammes d'alcool : ");
                 if ((*it)->canHeDrive()){
                    lcd.setRGB(0,255,0);
                }
                else {
                    lcd.setRGB(255,0,0);
                }
                lcd.setCursor(0,0);
                Serial.println((*it)->get_i0());
                lcd.setCursor(1,0);
                Serial.println((*it)->get_i1());
                lcd.setCursor(4,0);
                Serial.println((*it)->get_actual_grams());
                lcd.setCursor(9,0);
                Serial.println("grammes");
               
                delay(100);
                while(digitalRead(Push)!=HIGH){yield();}
                delay(100);
                computeGrams();
                it++;
            }
            standby=true;            
        }
        

        else if (1024*2/4<analogRead(0) && analogRead(0)<1024*3/4) {
            lcd.clear();
            m_level=1;
        }

        else{
            standby=true;
        }

        lcd.setRGB(255,255,0);
    }
    
    //GESTION DE LA CONSOMMATION
    else if (m_level==1){  

        while(digitalRead(Push)!=HIGH){
            yield();            
            lcd.clear();
            computeGrams();
            if (analogRead(Pot)<1024/2){
                Serial.println(m1[0]); //S??lection USER
            }
            else
                Serial.println(m1[1]);//Retour
                delay(100);
        }

        delay(200);

        if (analogRead(Pot)<1024/2){
            //Selection Utilisateur qui consomme.
            delay(100);
            m_level=2;
        }
        else{
            //RETOUR ?? m0
            m_level=0;
            standby=true;
        }
    }
        
    if (m_level ==2){
        while (m_level==2){
            lcd.clear();
            computeGrams();
            yield();
            delay(200);
            it = l_user.begin();

            while (digitalRead(Push)!= HIGH) {
                yield();
                delay(100);
                lcd.clear();
                if (analogRead(Pot)<1024/3){
                    lcd.setCursor(0,0);
                    Serial.println((*it)->get_i0());
                    lcd.setCursor(1,0);
                    Serial.println((*it)->get_i1());
                    lcd.setCursor(3,0);
                    Serial.println("Prev. User");
                }
                else if (analogRead(Pot)> 2*1024/3){
                    lcd.setCursor(0,0);
                    Serial.println((*it)->get_i0());
                    lcd.setCursor(1,0);
                    Serial.println((*it)->get_i1());
                    lcd.setCursor(3,0);
                    Serial.println("Next User");

                }
                else{
                    lcd.setCursor(0,0);
                    Serial.println((*it)->get_i0());
                    lcd.setCursor(1,0);
                    Serial.println((*it)->get_i1());
                    lcd.setCursor(3,0);
                    Serial.println("This User");
                }
            }
            delay(200);
            if (analogRead(Pot)<1024/3 && it!= l_user.begin()){
                it--;                
            }
            else if (analogRead(Pot)>2*1024/3 && it != l_user.end()){
                it++;    
            }
            else {
                (*it)->addConso();
                m_level=0;
            }
            delay(200);
        }
        delay(200);
        standby=true;
    }
}

char menu::set_i0(){
    lcd.clear();
    lcd.setCursor(0,0);
    Serial.println("Premiere initiale");
    delay(1000);

    while (digitalRead(Push)!=HIGH){
        lcd.clear();
        Serial.println(char(97+analogRead(0)/39));
        delay(100);
        yield();
    }
    delay(200);
    return char(65+analogRead(0)/39);
}

char menu::set_i1(){
    lcd.clear();
    Serial.println("Deuxieme initiale");
    delay(1000);
    while (digitalRead(Push)!=HIGH){
        lcd.clear();
        Serial.println(char(97+analogRead(0)/39));
        computeGrams();
        yield();
        delay(100);
    }
    delay(200);
    return char(65+analogRead(0)/39);
}

int menu::set_weight(){
    lcd.clear();
    Serial.println("Cmb Pesez vous ?");
    delay(1000);
    while (digitalRead(Push)!=HIGH){    
        lcd.clear();
        lcd.setCursor(2,0);
        Serial.println(40+(analogRead(0)/9));
        delay(100);
        computeGrams();
        yield();
    }
    delay(200);
    return 40+analogRead(0)/9;
}
char menu::set_sexe(){
    lcd.clear();
    Serial.println("Quel est votre sexe ?");
    delay(1000);
    while (digitalRead(Push)!=HIGH){
        lcd.clear();
        lcd.setCursor(2,0);
        computeGrams();
        yield();    
        if (analogRead(Pot)<1024/2){
            Serial.println("Homme");
        }
        else{
            Serial.println("Femme");
        }
        delay(100);
    }
    if (analogRead(Pot)<1024/2)
        return 'h';
    else
        return 'f';
}

float menu::set_height(){
    lcd.clear();
    Serial.println("Cmb mesurez vous ?");
    delay(1000);
    while (digitalRead(Push)!=HIGH){
        lcd.clear();
        lcd.setCursor(1,0);
        computeGrams();
        Serial.println(120+(analogRead(0)/10));
        lcd.setCursor(6,0);
        Serial.println("cm");
        yield();
        delay(100);
    }
    delay(200);
    return 1.2+(analogRead(0)/10)/100.0;
}

void menu::menu_init(){
    rgb_lcd lcd;
    lcd.begin(16,2);
    lcd.setRGB(255,255,0);
    lcd.clear();
    delay(300);
}

void menu::addPlayer(int user_type){
    //expert
    if (user_type==1){
        l_user.push_back(new expert(set_i0(), set_i1(), set_weight(), set_height(), set_sexe()));
    }
    //young
    else{
        l_user.push_back(new young(set_i0(), set_i1(), set_weight(), set_height(), set_sexe()));
    }
    
}

void menu::addToList(user*newU){
    l_user.push_back(newU);
}

void menu::computeGrams(){
  list<user*>::iterator it ;
  myList = main_menu.get_list();
  for (it = myList.begin(); it!= myList.end(); it++){
    if ((*it)->get_sexe() == 'f'){
      (*it)->set_actual_grams((*it)->get_actual_grams()-0.085*(millis()-(*it)->get_time())/3600000);
      //(*it)->set_actual_grams((*it)->get_actual_grams()+0.01);
    }
    else if ((*it)->get_sexe() == 'h'){
      (*it)->set_actual_grams((*it)->get_actual_grams()-(0.1*(millis()-(*it)->get_time())/3600000));
    }
    
    (*it)->set_time(millis());
  }
}

#endif
