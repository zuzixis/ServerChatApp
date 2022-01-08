//
// Created by Jakub Rončák on 26/12/2021.
//

#pragma once

#include <vector>
#include "models/User.h"

using namespace std;

class User;

class ActiveUsersProvider {
    int actualUserId = 0;
    vector<User *> activeUsers = vector<User *>();
public:
//    static ActiveUsersProvider *instance = {};
    ActiveUsersProvider() {}

//    ~ActiveUsersProvider() {
//        std::for_each( activeUsers->begin(), activeUsers->end(), []( User* u ) { delete u; } );
//
////        for (auto u: *activeUsers) {
////            delete u;
////        }
//        delete activeUsers;
//    }
//    virtual ~ActiveUsersProvider();


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

    vector<User *> getById(int id);

    void removeUser(const User *u);

    const vector<User *> getActiveUsers();

    User *getLastUser();

    int getActualUserId() const;

    void setActualUserId(int actualUserId);
};

