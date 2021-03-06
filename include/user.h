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

    float actual_grams;
    float max_grams = 0.2;
    unsigned long time;

public:
    user(char initial0, char initial1, int pweight, float pheight, char psexe);
    
    //Getters

    char get_i0();
    char get_i1();
    int get_weight();
    float get_height();
    float get_actual_grams();
    char get_sexe(){return sexe;};
    unsigned long get_time(){return time;};
    bool canHeDrive(){return (this->actual_grams)<(this->max_grams);};

    //Setters

    void set_actual_grams(float g);
    void set_time(unsigned long mTime);


    //Methods
    virtual void addConso();
    void operator++();
};

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

float user::get_actual_grams(){
    return this->actual_grams;
}

void user::set_actual_grams(float g){
    this->actual_grams=g;
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
    }
    else if (sexe == 'h'){
        actual_grams+= DOSE/(weight*0.7);
    }
}
void user::set_time(unsigned long mTime){
    time = mTime;
}



#endif //info_H