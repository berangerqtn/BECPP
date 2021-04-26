#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
using namespace std;

class user {

protected:
    string name;
    int weight;
    float height;
    float IMC;
    float actual_grams;
    int min_to_wait;
    int time;
public:
    int get_weight();
    float get_height();
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
    while (digitalRead(5)!=HIGH){
        Serial.println(40+(analogRead(0)/9));
        yield();
    }
    this->weight=40+analogRead(0)/9;
    delay(200);
    Serial.println("Voulez pesez  : " + this->weight);
    delay(2000);
    //while(digitalRead(5)!=HIGH){}
    

    Serial.println("Combien mesurez vous ?");
    while (digitalRead(5)!=HIGH){
        Serial.println(120+(analogRead(0)/10));
        yield();
    }
    this->height=1.2+(analogRead(0)/10)/100.0;
    delay(200);
    Serial.println("Voulez mesurez : " + this->weight);
    delay(2000);
    //while(digitalRead(5)!=HIGH){}

    this->IMC=this->weight/((this->height)*(this->height));
    Serial.println("Vous avez un IMC de : " + String(this->IMC));

    delay(2000);

    Serial.println("BILAN UTILISATEUR");
    Serial.println("Poids : " + String(this->get_weight()));
    Serial.println("Taille : " + String(this->get_height()));
    Serial.println("IMC : "+ String(this->get_IMC()));
}

int user::get_weight(){
    return this->weight;
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