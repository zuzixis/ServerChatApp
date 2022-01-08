//
// Created by Jakub Rončák on 26/12/2021.
//

#include "ActiveUsersProvider.h"

void ActiveUsersProvider::addUser(User *u) {
    this->activeUsers.push_back(u);
}

void ActiveUsersProvider::removeUser(const User *u) {

    cout << this->activeUsers.size() << endl;
    delete u;
//    std::vector<int>& vec = myNumbers; // use shorter name
    this->activeUsers.erase(std::remove(this->activeUsers.begin(), this->activeUsers.end(), u),
                             this->activeUsers.end());

//    vector<User *u>::iterator new_end = remove(this->activeUsers.begin(), this->activeUsers.end(), u);
    cout << this->activeUsers.size() << endl;

    //TODO: skontrolovat
}


const vector<User *> ActiveUsersProvider::getActiveUsers() {
    return activeUsers;
}

User *ActiveUsersProvider::getLastUser() {
    return activeUsers.back();
}

vector<User *> ActiveUsersProvider::getById(int id) {
    vector<User *> ret; // TODO: netreba alokovat cez new?

    copy_if(this->activeUsers.begin(), this->activeUsers.end(),
            back_inserter(ret), [id](User *u) { return u->getId() == id; });

    return ret;
}

int ActiveUsersProvider::getActualUserId() const {
    return actualUserId;
}

void ActiveUsersProvider::setActualUserId(int actualUserId) {
    ActiveUsersProvider::actualUserId = actualUserId;
}

//ActiveUsersProvider::~ActiveUsersProvider() {
//    std::for_each(activeUsers.begin(), activeUsers.end(), [](User *u) { delete u; });
//
////        for (auto u: *activeUsers) {
////            delete u;
////        }
//    delete activeUsers;
//}


