#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
using namespace std;

class info {

protected:
    string name;
    int weight;
    int height;
    float IMC;
public:
    int get_weight();
    int get_height();
    float get_IMC();
    void set_info();
};

class user:info{
protected:
    float actual_grams;
    int min_to_wait;
    int time;

public:
    user();
    void set_actual_grams();
    float get_actual_grams();
    void swap_users(user *ut);
};


void info::set_info(){

    //Serial.println("Première initiale ?");

    Serial.println("Combien Pesez vous ?");
    while (digitalRead(16)!=1){
        Serial.println(40+(analogRead(0)/9));
    }
    this->weight=40+analogRead(0)/9;
    delay(1000);

    Serial.println("Voulez vous valider ce poids : " + this->weight);
    while(digitalRead(16)!=1){

    }

    Serial.println("Combien mesurez vous ?");
    while (digitalRead(16)!=1){
        Serial.println(120+(analogRead(0)/10));
    }
    this->weight=120+(analogRead(0)/10)/100;

    Serial.println("Voulez vous valider cette taille : " + this->weight);
    while(digitalRead(16)!=1){
        
    }

    this->IMC=this->weight/(float(this->height*this->height));

    Serial.println("Poids : " + this->get_weight());
    Serial.println("Taille : " + this->get_height());
    Serial.print("IMC : ");
    Serial.print( this->get_IMC());
}

int info::get_weight(){
    return this->weight;
}

int info::get_height(){
    return this->height;
}

float info::get_IMC(){
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

#endif //info_H