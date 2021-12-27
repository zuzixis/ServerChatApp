//
// Created by Jakub Rončák on 26/12/2021.
//

#pragma once

#include <vector>
#include "../models/User.h"

using namespace std;

class ActiveUsersProvider {
    vector<User *> *activeUsers = new vector<User *>();

//    static ActiveUsersProvider *instance = {};
    ActiveUsersProvider() {}

public:
    static ActiveUsersProvider &getInstance() {
        static ActiveUsersProvider theInstance;
        return theInstance;
    }

//    ActiveUsersProvider(){
//        if(instance == nullptr){
//            instance = new ActiveUsersProvider();
//        }
//    }
    void addUser(User *u);

    void removeUser(const User *u);

    const vector<User *> *getActiveUsers();

    User *getLastUser();
};

