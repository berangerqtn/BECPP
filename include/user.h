#ifndef USER_H
#define USER_H
#include <Arduino.h>
#include "rgb_lcd.h"
#include <string>

//rgb_lcd lcd;

int Push = 16;
int Pot = 0;
int nbUser=0;

using namespace std;

class user {

protected:
    char i0;
    char i1;
    char sexe;

    int weight;
    float height;
    float IMC;


    float actual_grams;
    int min_to_wait;

    unsigned long time;

public:
    user(char initial0, char initial1, int pweight, float pheight, char psexe);
    
    //getters
    char get_i0();
    char get_i1();
    int get_weight();
    float get_height();
    float get_IMC();
    float get_actual_grams();
    char get_sexe(){return sexe;};
    unsigned long get_time(){return time;};

    //setters
    void set_actual_grams(float g);
    void set_info();
    void set_time(unsigned long mTime);

    //methods
    void swap_users(user *ut);    
    void addConso();
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


    this->IMC=this->weight/((this->height)*(this->height));
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
    this->IMC=this->weight/((this->height)*(this->height));
    this->sexe = psexe;
    this->min_to_wait=0;
    this->actual_grams=0;

    time = millis();

    nbUser++;
}

class young:public user{
protected:
    const float max_grams = 0.25;
public:
    bool canHeDrive();
    young(char initial0, char initial1, int pweight, float pheight, char psexe);
};

young::young(char initial0, char initial1, int pweight, float pheight, char psexe):user(initial0, initial1, pweight, pheight, psexe){}

class expert:public user{
protected:
    const float max_grams = 0.5;
public:
    bool canHeDrive();
    expert(char initial0, char initial1, int pweight, float pheight, char psexe);

};

expert::expert(char initial0, char initial1, int pweight, float pheight, char psexe):user(initial0, initial1, pweight, pheight, sexe){}

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

float user::get_IMC(){
    return this->IMC;
}

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

bool young::canHeDrive(){
    if (actual_grams>max_grams)
        return false;
    else
        return true;
}

bool expert::canHeDrive(){
    if (actual_grams>max_grams)
        return false;
    else
        return true;
}

void user::addConso(){
    if (sexe == 'f'){
        actual_grams = actual_grams + 10/(weight*0.6);
    }
    else if (sexe == 'h'){
        actual_grams = actual_grams + 10/(weight*0.7);
    }    
}

void user::set_time(unsigned long mTime){
    time = mTime;
}



#endif //info_H