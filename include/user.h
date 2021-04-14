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
    int get_weight() const;
    int get_height() const;
    float get_IMC() const;
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
    float get_actual_grams() const;
    void swap_users(user *ut);
    void print_user();
    bool operator>(const user& right_user);  

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
}

int info::get_weight() const{
    return this->weight;
}

int info::get_height() const{
    return this->height;
}

float info::get_IMC() const{
    return this->IMC;
}

void user::print_user(){
    Serial.println("Poids : " + this->get_weight());
    Serial.println("Taille : " + this->get_height());
    Serial.print("IMC : ");
    Serial.print( this->get_IMC());
}

void user::swap_users(user *ut){
    user temp=*ut;
    *ut=*this;
    *this=temp;
}

float user::get_actual_grams() const{
    return this->actual_grams;
}

bool user::operator>(const user& right_user){
    if (get_actual_grams()>right_user.get_actual_grams()) {
        return true;
    }
    else{ return false;}
}
#endif //info_H