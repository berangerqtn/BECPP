#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

class info {

private:
    int weight;
    int height;
    float IMC;
public:
    info();
    info(int w, int h);
    int get_weight();
    int get_height();
    float get_IMC();
    void set_IMC();
};

class user:info{
private:
    float actual_grams;
    int min_to_wait;
    int time;

public:
    user();
    void set_actual_user();
    float get_actual_grams();
    void swap_users(user *ut);
    bool operator>(user& right_user);  
    

};

info::info(){

}

void info::set_IMC(){
    if (this->weight!=0)
        this->IMC=this->weight/(float(this->height*this->height));
}

float user::get_actual_grams(){
    return actual_grams;
}

void user::swap_users(user *ut){
    user temp=*ut;
    *ut=*this;
    *this=temp;
}

bool user::operator>(const user& right_user){
    if (get_actual_grams()>right_user.get_actual_grams()) return true;
}


#endif //info_H