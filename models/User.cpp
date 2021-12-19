//
// Created by Jakub Rončák on 19/12/2021.
//

#include "User.h"


User::User(int id, const string &name, const string &password) : id(id), name(name), password(password) {
//    this->x::AAA;
}

int User::getId() const {
    return id;
}

void User::setId(int id) {
    User::id = id;
}

int User::getPort() const {
    return port;
}

void User::setPort(int port) {
    User::port = port;
}

const string &User::getName() const {
    return name;
}

void User::setName(const string &name) {
    User::name = name;
}

const string &User::getPassword() const {
    return password;
}

void User::setPassword(const string &password) {
    User::password = password;
}

const string &User::getIpAddress() const {
    return ipAddress;
}

void User::setIpAddress(const string &ipAddress) {
    User::ipAddress = ipAddress;
}

bool User::isParIsLogged() const {
    return parIsLogged;
}

void User::setParIsLogged(bool parIsLogged) {
    User::parIsLogged = parIsLogged;
}

bool User::save() {
    return false;
}

bool User::update() {
    return false;
}

bool User::remove() {
    return false;
}

vector<Message *> *User::getMessages() const {
    return messages;
}

vector<Contact *> *User::getContacts() const {
    return contacts;
}

vector<Group *> *User::getGroups() const {
    return groups;
}


