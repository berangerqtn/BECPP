#ifndef USER_LIST_H
#define USER_LIST_H

#include <iostream>
#include <list>
#include "user.h"



using namespace std;

class user_list {
    public : 
    void add_user(user* user);
    void swap_user(list<user*>::iterator it1, list<user*>::iterator it2);
    void sort_list();
    void print_list();
    private :
    list<user*> u_list;
    list<user*>::iterator it;

    protected :

};



void user_list::add_user(user* user){
    u_list.push_back(user);
}

/*void user_list::swap_user(list<user*>::iterator it1, list<user*>::iterator it2){
    user * temp = u_list[it1];
    u_list[it1] = u_list[it2];
    u_list[it2] = temp;
}*/
void user_list::swap_user(list<user*>::iterator it1, list<user*>::iterator it2){
    user * temp = *it1;
    *it1 = *it2;
    *it2 = temp;
}

void user_list::sort_list(){
    for (it=u_list.begin(); it!= u_list.end()--; it++){
        if (*it > *(it++)){
            swap_user(it, it++);
        }
    }
}

void user_list::print_list(){
    for (it=u_list.begin(); it!=u_list.end() ; it++){
        (**it).print_user();
    }
}

#endif