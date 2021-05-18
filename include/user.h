#ifndef USER_H
#define USER_H
#include <Arduino.h>
#include "rgb_lcd.h"
#include <string>

//rgb_lcd lcd;

#define Push  16
#define Pot  0
#define DOSE 10.0

int nbUser=0;

using namespace std;

class user {

protected:
    char i0;
    char i1;
    char sexe;
    int weight;
    float height;
    //float IMC;

    float actual_grams;
    float max_grams = 0.2;
    unsigned long time;

public:
    user(char initial0, char initial1, int pweight, float pheight, char psexe);
    
    //getters
    char get_i0();
    char get_i1();
    int get_weight();
    float get_height();
    float get_actual_grams();
    char get_sexe(){return sexe;};
    unsigned long get_time(){return time;};
    bool canHeDrive(){return (this->actual_grams)<(this->max_grams);};

    //setters
    void set_actual_grams(float g);
    void set_info();
    void set_time(unsigned long mTime);
    virtual void addConso();
    void operator++();
    //methods
    void swap_users(user *ut);    
    bool operator > (user& right_user);
};

void user::set_info(){

    //lcd.print("Combien Pesez vous ?");
    while (digitalRead(Push)!=HIGH){
        //lcd.print(40+(analogRead(0)/9));
        yield();
    }
    this->weight=40+analogRead(0)/9;
    delay(200);
    //lcd.print("Voulez pesez  : " + this->weight);
    delay(2000);
    

    //lcd.print("Combien mesurez vous ?");
    while (digitalRead(Push)!=HIGH){
        //lcd.print(120+(analogRead(0)/10));
        yield();
    }
    this->height=1.2+(analogRead(0)/10)/100.0;
    delay(200);
    //lcd.print("Voulez mesurez : " + this->weight);
    delay(2000);


    //this->IMC=this->weight/((this->height)*(this->height));
    //lcd.print("Vous avez un IMC de : " + String(this->IMC));

    delay(2000);

    //lcd.print("BILAN UTILISATEUR");
    //lcd.print("Poids : " + String(this->get_weight()));
    //lcd.print("Taille : " + String(this->get_height()));
    //lcd.print("IMC : "+ String(this->get_IMC()));
    nbUser++;
}

user::user(char initial0, char initial1, int pweight, float pheight, char psexe){
    this->i0=initial0;
    this->i1=initial1;
    this->height=pheight;
    this->weight=pweight;
    this->sexe = psexe;
    this->actual_grams=0;

    time = millis();

    nbUser++;
}

class expert:public user{
protected:
    const float max_grams = 0.5;
public:
    bool canHeDrive(){return this->actual_grams<this->max_grams;};
    expert(char initial0, char initial1, int pweight, float pheight, char psexe);

};

expert::expert(char initial0, char initial1, int pweight, float pheight, char psexe):user(initial0, initial1, pweight, pheight, psexe){}

class young:public user{
protected:
    float max_grams = 0.1;
public:
    bool canHeDrive(){return this->actual_grams<this->max_grams;};
    young(char initial0, char initial1, int pweight, float pheight, char psexe);

};

young::young(char initial0, char initial1, int pweight, float pheight, char psexe):user(initial0, initial1, pweight, pheight, psexe){}


int user::get_weight(){
    return this->weight;
}

char user::get_i0(){
    return i0;
}

char user::get_i1(){
    return i1;
}

float user::get_height(){
    return this->height;
}

/*float user::get_IMC(){
    return this->IMC;
}*/

void user::swap_users(user *ut){
    user temp=*ut;
    *ut=*this;
    *this=temp;
}

float user::get_actual_grams(){
    return this->actual_grams;
}

void user::set_actual_grams(float g){
    this->actual_grams=g;
}

bool user::operator>(user& right_user){
    if (this->get_actual_grams()>right_user.get_actual_grams()) {
        return true;
    }
    else return false;
}

void user::operator++()
{
    if (sexe == 'f'){
        actual_grams+= DOSE/(weight*0.6);
    }
    else if (sexe == 'h'){
        actual_grams+= DOSE/(weight*0.7);
    }    
    Serial.println("Grammes actuels : ");
    Serial.println(this->get_actual_grams());
}

void user::addConso()
{
    if (sexe == 'f'){
        actual_grams+= DOSE/(weight*0.6);
        Serial.println("Détail conso user: ");
        Serial.println("Poids : ");
        Serial.println(this->get_weight());
        Serial.println(this->get_actual_grams());
    }
    else if (sexe == 'h'){
        actual_grams+= DOSE/(weight*0.7);
    }
}
void user::set_time(unsigned long mTime){
    time = mTime;
}



#endif //info_H