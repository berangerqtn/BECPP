#ifndef MENU_H
#define MENU_H

#include <map>
#include <list>
#include "rgb_lcd.h"
#include "user.h"

rgb_lcd lcd;

class menu{
protected :
    std::map<int,String> m0; //Premier niveau de menu
    std::map<int,String> m1; //Sous menu de Consommation
    list<user> l_user;
    list<user>::iterator it;

    int m_level;

public :
    void menu_display();

    char set_i0();
    char set_i1();
    int set_weight();
    float set_height();

    menu();
};

menu::menu(){
    m0[0]= "Ajouter un joueur";
    m0[1]="Voir Utilisateurs";
    m0[2]="Consommer";

    m1[0]="Sélection Utilisateur";
    m1[1]="Retour";
    m_level=0;
}

void menu::menu_display(){
    if (m_level==0){
        Serial.println("On est au niveau 0");
        
        while(digitalRead(Push)!=HIGH){
            if (analogRead(Pot)<1024/3)
                Serial.println(m0[0]);

            else if (1024/3<analogRead(Pot) && analogRead(Pot)<1024*2/3)
                Serial.println(m0[1]);

            else
                Serial.println(m0[2]);
        }

        if (analogRead(0)<1024/3){
            //ADD USERS
            Serial.println("Quel âge avez vous ?");
            while (digitalRead(Push)!=HIGH){
                Serial.println(18+analogRead(Pot)/13);
                yield();
            }
            if (18+analogRead(Pot)/13<22){
                young newUser(set_i0(), set_i1(), set_weight(), set_height());
                l_user.push_back(newUser);
            }
            else{
                expert newUser(set_i0(), set_i1(), set_weight(), set_height());
                l_user.push_back(newUser);
            }
            
        }
        else if (1024/3<analogRead(0) && analogRead(0)<1024*2/3){
            //SEE USERS
            it=l_user.begin();
            while (it!=l_user.end()){
                Serial.print((*it).get_i0()+(*it).get_i1()+" grammes d'alcool : ");
                it++;
            }
            
        }

        else {
            //Consommer
            m_level=1;
        }
        
    }
    
    //GESTION DE LA CONSOMMATION
    else if (m_level==1){  

        while(digitalRead(Push)!=HIGH){
            if (analogRead(Pot)<1024/2)
                Serial.println(m1[0]); //Sélection USER
            else
                Serial.println(m1[1]);//Retour
        }
        if (analogRead(Pot)<1024/2){
            //A COMPLETER Selection Utilisateur qui consomme.
        }
        else{
            m_level=0;
        }
    }
}

char menu::set_i0(){
    Serial.println("Première initiale");
    while (digitalRead(Push)!=HIGH){
        Serial.println(65+analogRead(0)/39);
        yield();
    }
    return 65+analogRead(0)/39;
}

char menu::set_i1(){
    Serial.println("Deuxième initiale");
    while (digitalRead(Push)!=HIGH){
        Serial.println(65+analogRead(0)/39);
        yield();
    }
    return 65+analogRead(0)/39;
}

int menu::set_weight(){
    Serial.println("Combien Pesez vous ?");
    while (digitalRead(Push)!=HIGH){
        Serial.println(40+(analogRead(0)/9));
        yield();
    }
    return 40+analogRead(0)/9;
}

float menu::set_height(){
    Serial.println("Combien mesurez vous ?");
    while (digitalRead(Push)!=HIGH){
        Serial.println(120+(analogRead(0)/10));
        yield();
    }
    return 1.2+(analogRead(0)/10)/100.0;
}


#endif