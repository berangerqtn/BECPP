#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

class user {

private:
    int weight;
    int height;
    float IMC;
public:
    user();
    user(int w, int h);
    int get_weight();
    int get_height();
    float get_IMC();
    void set_IMC();
};

class grams:user{
private:
    float actual_grams;
    int min_to_wait;
    int time;

public:
    grams();
    void set_actual_grams();

};

user::user(){

}

void user::set_IMC(){
    if (this->weight!=0)
        this->IMC=this->weight/(float(this->height*this->height));
}


#endif //USER_H