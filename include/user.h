#ifndef USER_H
#define USER_H
#include <Arduino.h>

int Push = 5;
int Pot = 0;
int nbUser=0;

using namespace std;

class user {

protected:
    char i0;
    char i1;

    int weight;
    float height;
    float IMC;

    float actual_grams;
    int min_to_wait;

public:
    user(char initial0, char initial1, int pweight, float pheight);
    
    char get_i0();
    char get_i1();
    int get_weight();
    float get_height();
    float get_IMC();
    void set_actual_grams(float g);
    float get_actual_grams();
    void swap_users(user *ut);
    void set_info();

    bool operator > (user& right_user);
};

void user::set_info(){

    Serial.println("Combien Pesez vous ?");
    while (digitalRead(Push)!=HIGH){
        Serial.println(40+(analogRead(0)/9));
        yield();
    }
    this->weight=40+analogRead(0)/9;
    delay(200);
    Serial.println("Voulez pesez  : " + this->weight);
    delay(2000);
    

    Serial.println("Combien mesurez vous ?");
    while (digitalRead(Push)!=HIGH){
        Serial.println(120+(analogRead(0)/10));
        yield();
    }
    this->height=1.2+(analogRead(0)/10)/100.0;
    delay(200);
    Serial.println("Voulez mesurez : " + this->weight);
    delay(2000);


    this->IMC=this->weight/((this->height)*(this->height));
    Serial.println("Vous avez un IMC de : " + String(this->IMC));

    delay(2000);

    Serial.println("BILAN UTILISATEUR");
    Serial.println("Poids : " + String(this->get_weight()));
    Serial.println("Taille : " + String(this->get_height()));
    Serial.println("IMC : "+ String(this->get_IMC()));
    nbUser++;
}

user::user(char initial0, char initial1, int pweight, float pheight){
    this->i0=initial0;
    this->i1=initial1;
    this->height=pheight;
    this->weight=pweight;
    this->IMC=this->weight/((this->height)*(this->height));

    this->min_to_wait=0;
    this->actual_grams=0;
    nbUser++;
}

class young:public user{
protected:
    const float max_grams = 0.25;
public:
    bool canHeDrive();
    young(char initial0, char initial1, int pweight, float pheight);
};

young::young(char initial0, char initial1, int pweight, float pheight):user(initial0, initial1, pweight, pheight){}

class expert:public user{
protected:
    const float max_grams = 0.5;
public:
    bool canHeDrive();
    expert(char initial0, char initial1, int pweight, float pheight);

};

expert::expert(char initial0, char initial1, int pweight, float pheight):user(initial0, initial1, pweight, pheight){}

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

bool user::operator>(user& right_user){
    if (this->get_actual_grams()>right_user.get_actual_grams()) {
        return true;
    }
    else return false;
}

void user::set_actual_grams(float g){
    this->actual_grams=g;
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

#endif //info_H