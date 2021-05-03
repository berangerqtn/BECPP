#ifndef MENU_H
#define MENU_H

#include <map>
#include <list>
#include "user.h"

class menu{
protected :
    std::map<int,String> m0; //Premier niveau de menu
    std::map<int,String> m1; //Sous menu de Consommation
    list<user> l_user;

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
}

void menu::menu_display(){
    if (m_level==0){
        Serial.println("On est au niveau 0");
        
        while(digitalRead(Push)!=HIGH){
            if (analogRead(Pot)<1024/3)
                Serial.println(m0[0]);

            else if (analogRead(Pot))
                Serial.println(m0[1]);

            else
                Serial.println(m0[2]);

        }

        if (analogRead(0)<1024/3){
            //ADD USERS
            user newUser(set_i0(), set_i1(), set_weight(), set_height());
            l_user.push_back(newUser);
        }
        else if (1024/3<analogRead(0) && analogRead(0)<1024*2/3){
            //SEE USERS
            

        }

        else {
            //Consommer
        }

        
    }
    else if (m_level==1){
        Serial.println("On est au niveau 1");

        if (digitalRead(Push)==HIGH){
            m_level=0;
            delay(200);
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