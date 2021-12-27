//
// Created by Jakub Rončák on 26/12/2021.
//

#include "ActiveUsersProvider.h"

void ActiveUsersProvider::addUser(User *u) {
    this->activeUsers->push_back(u);
    this->activeUsers->push_back(u);
}

void ActiveUsersProvider::removeUser(const User *u) {

    remove(this->activeUsers->begin(), this->activeUsers->end(), u);
    //TODO: skontrolovat
}

const vector<User *> *ActiveUsersProvider::getActiveUsers() {
    return activeUsers;
}

User *ActiveUsersProvider::getLastUser() {
    return activeUsers->back();
}
