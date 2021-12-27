#include "User.h"
//
// Created by Jakub Rončák on 19/12/2021.
//

int User::getId() const {
    return id;
}

void User::setId(int id) {
    User::id = id;
}

const string &User::getName() const {
    return name;
}

void User::setName(const string &name) {
    User::name = name;
}
//
//vector<Message *> *User::getMessages() const {
//    return messages;
//}

vector<Contact *> *User::getContacts() const {
    return contacts;
}

vector<Group *> *User::getGroups() const {
    return groups;
}

//Model *User::get() {
//    //TODO:implementacia get
//    return nullptr;
//}
//
//bool User::save() {
//    //TODO:implementacia save
//    return false;
//}
//
//bool User::update() {
//    //TODO:implementacia update
//    return false;
//}
//
//bool User::remove(int id) {
//    //TODO:implementacia remove
//    return false;
//}

//void User::setMessages(vector<Message *> *messages) {
//    User::messages = messages;
//}

void User::setContacts(vector<Contact *> *contacts) {
    User::contacts = contacts;
}

//const sockaddr_in &User::getAddress() const {
//    return address;
//}
//
//void User::setAddress(const sockaddr_in &address) {
//    User::address = address;
//}

int User::getSockfd() const {
    return sockfd;
}

void User::setSockfd(int sockfd) {
    User::sockfd = sockfd;
}

void User::setGroups(vector<Group *> *groups) {
    User::groups = groups;
}



