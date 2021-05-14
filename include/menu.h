#ifndef MENU_H
#define MENU_H

#include <map>
#include <list>
#include "rgb_lcd.h"
#include "user.h"

#define DOSE 10.0

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
    void addPlayer(user& u);
    void addPlayer(young& u);
    void addPlayer(expert& u);
    void computeGrams();

    menu();
    void menu_init();
    void add_to_list(user newU);

};

menu main_menu;
list<user*> myList = main_menu.get_list();


menu::menu(){
    m0[0]= "Ajouter un joueur";
    m0[1]="Voir Utilisateurs";
    m0[2]="Consommer";

    m1[0]="Sélection Utilisateur";
    m1[1]="Retour";
    m_level=0;
}

void menu::add_to_list(user newU){
    l_user.push_back(&newU);
}


void menu::menu_display(){
    if (m_level==0){
        //Serial.println("On est au niveau 0");
        
        while(digitalRead(Push)!=HIGH){
            lcd.clear();
            computeGrams();
            if (analogRead(Pot)<1024/3){
                Serial.println(m0[0]);
                Serial.println(m0[0]);
            }
            else if (1024/3<analogRead(Pot) && analogRead(Pot)<1024*2/3){
                Serial.println(m0[1]);
                Serial.println(m0[1]);
            }
            else{
                Serial.println(m0[2]);
                Serial.println(m0[2]);
            }
        }
        delay(200);

        if (analogRead(0)<1024/3){
            //ADD USERS
            Serial.println("Quel âge avez vous ?");
            Serial.println("Quel age avez vous ?");
            while (digitalRead(Push)!=HIGH){
                Serial.println(18+analogRead(Pot)/13);
                Serial.println(18+analogRead(Pot)/13);
                computeGrams();
                yield();
            }
            delay(200);
            if (18+analogRead(Pot)/13<22){
                young newUser(set_i0(), set_i1(), set_weight(), set_height(), set_sexe());
                main_menu.addPlayer(newUser);
                Serial.print("User Créé");
            }
            else{
                expert newUser(set_i0(), set_i1(), set_weight(), set_height(), set_sexe());
                main_menu.addPlayer(newUser);
                Serial.print("User Créé");

            }
            
        }
        else if (1024/3<analogRead(0) && analogRead(0)<1024*2/3){
            //SEE USERS
            it=l_user.begin();
            while (it!=l_user.end()){
                //Serial.print((*it).get_i0()+(*it).get_i1()+" grammes d'alcool : ");
                Serial.println((*it)->get_i0()+(*it)->get_i1()+" grammes d'alcool : ");
                Serial.println((*it)->get_actual_grams());
                while(digitalRead(Push)!=HIGH){yield();}
                delay(200);
                computeGrams();
                it++;
            }
        }

        else {
            m_level=1;
        }
        
    }
    
    //GESTION DE LA CONSOMMATION
    else if (m_level==1){  

        while(digitalRead(Push)!=HIGH){
            lcd.clear();
            computeGrams();
            if (analogRead(Pot)<1024/2)
                Serial.println(m1[0]); //Sélection USER
            else
                Serial.println(m1[1]);//Retour
        }


        if (analogRead(Pot)<1024/2){
            //A COMPLETER Selection Utilisateur qui consomme.
            it = l_user.begin();
            while (digitalRead(Push)!=HIGH){
                computeGrams();
                yield();
                
                if (analogRead(Pot)<1024/3 && it!= l_user.begin()){
                    Serial.println((*it)->get_i0() + (*it)->get_i1());
                    lcd.setCursor(1,0);
                    Serial.println("Prev. User");
                }
                else if (analogRead(Pot)> 2*1024/3 && it != l_user.end()){
                    Serial.println((*it)->get_i0() + (*it)->get_i1());
                    lcd.setCursor(1,0);
                    Serial.println("Next User");

                }
                else{
                    Serial.println((*it)->get_i0() + (*it)->get_i1());
                    lcd.setCursor(1,0);
                    Serial.println("This User");
                }
            }
            if (analogRead(Pot)<1024/3){
                it--;
            }
            else if (analogRead(Pot)>2*1024/3){
                it++;
            }
            else {
                (*it)->addConso();
            }
            
        }
        else{
            //RETOUR à m0
            m_level=0;
        }
    }
}

char menu::set_i0(){
    lcd.clear();
    Serial.println("Première initiale");
    while (digitalRead(Push)!=HIGH){
        lcd.clear();
        Serial.println(char(65+analogRead(0)/39));
        yield();
    }
    delay(200);
    return char(65+analogRead(0)/39);
}

char menu::set_i1(){
    lcd.clear();
    Serial.println("Deuxième initiale");
    while (digitalRead(Push)!=HIGH){
        lcd.clear();
        Serial.println(char(65+analogRead(0)/39));
        computeGrams();
        yield();
    }
    delay(200);
    return char(65+analogRead(0)/39);
}

int menu::set_weight(){
    lcd.clear();
    Serial.println("Cmb Pesez vous ?");
    while (digitalRead(Push)!=HIGH){
        lcd.clear();
        Serial.println(40+(analogRead(0)/9));
        computeGrams();
        yield();
    }
    delay(200);
    return 40+analogRead(0)/9;
}
char menu::set_sexe(){
    Serial.println("Quel est votre sexe ?");
    while (digitalRead(Push)!=HIGH){
        computeGrams();
        if (analogRead(Pot)<1024/2){
            Serial.println("Homme");
        }
        else{
            Serial.println("Femme");
        }
    }
    if (analogRead(Pot)<1024/2)
        return 'h';
    else
        return 'f';
}

float menu::set_height(){
    lcd.clear();
    Serial.println("Cmb mesurez vous ?");
    while (digitalRead(Push)!=HIGH){
        lcd.clear();
        computeGrams();
        Serial.println(120+(analogRead(0)/10));
        yield();
    }
    delay(200);
    return 1.2+(analogRead(0)/10)/100.0;
}

void menu::menu_init(){
    rgb_lcd lcd;
    lcd.begin(16,2);
    lcd.setRGB(255,0,0);
    lcd.clear();
    //Serial.println("blzblz");
    //Serial.print("hello");
    delay(3000);
}

void menu::addPlayer(user& u){
    l_user.push_back(&u);
}
void menu::addPlayer(young& u){
    l_user.push_back(&u);
}

void menu::addPlayer(expert& u){
    l_user.push_back(&u);
}
void menu::computeGrams(){
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

#endif
