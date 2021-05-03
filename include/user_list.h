#ifndef USER_LIST_H
#define USER_LIST_H

#include <iostream>
#include <list>
#include "user.h"


using namespace std;

class user_list {
    public : 
    user_list();
    void add_user(user* user);
    void swap_user(list<user*>::iterator it1, list<user*>::iterator it2);
    void sort_list();
    void print_list();

    private :
        list<user*> u_list = NULL;
        list<user*>::iterator it;
    protected :

}

user_list::user_list(){
    u_list =NULL;
}

void user_list::add_user(user* user){
    u_list.pop_back(user);
}

void user_list::swap_user(list<user*>::iterator it1, list<user*>::iterator it2){
    user * temp = u_list[it1];
    u_list[it1] = u_list[it2];
    u_list[it2] = temp;
}

void user_list::sort_list(){
    for (it=u_list.begin(); it!= u_list.end()-1; it++){
        if (*it > *(it+1)){
            swap_user(it, it+1);
        }
    }
}

#endif