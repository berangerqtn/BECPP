#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
using namespace std;

class user {

protected:
    string name;
    int weight;
    int height;
    float IMC;
    float actual_grams;
    int min_to_wait;
    int time;
public:
    int get_weight();
    int get_height();
    float get_IMC();
    void set_info();
    void set_actual_grams(float g);
    float get_actual_grams();
    void swap_users(user *ut);

    bool operator > (user& right_user);
};

class young:user{
protected:
    const float max_grams;
public:
    bool canHeDrive();
};

class expert:user{
protected:
    const float max_grams;
public:
    bool canHeDrive();

};

void user::set_info(){

    //Serial.println("Première initiale ?"); //Gestion des noms si plusieurs utilisateurs

    Serial.println("Combien Pesez vous ?");
    while (digitalRead(16)!=1){
        Serial.println(40+(analogRead(0)/9));
    }
    this->weight=40+analogRead(0)/9;
    delay(1000);

    Serial.println("Voulez vous valider ce poids : " + this->weight);
    while(digitalRead(16)!=1){}

    Serial.println("Combien mesurez vous ?");
    while (digitalRead(16)!=1){
        Serial.println(120+(analogRead(0)/10));
    }
    this->weight=120+(analogRead(0)/10)/100;

    delay(1000);
    Serial.println("Voulez vous valider cette taille : " + this->weight);
    while(digitalRead(16)!=1){

    }

    this->IMC=this->weight/(float(this->height*this->height));

    delay(1000);

    Serial.println("Poids : " + this->get_weight());
    Serial.println("Taille : " + this->get_height());
    Serial.print("IMC : ");
    Serial.print( this->get_IMC());
}

int user::get_weight(){
    return this->weight;
}

int user::get_height(){
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