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
    float actual_user;
    int min_to_wait;
    int time;

public:
    user();
    void set_actual_user();

};

info::info(){

}

void info::set_IMC(){
    if (this->weight!=0)
        this->IMC=this->weight/(float(this->height*this->height));
}


#endif //info_H