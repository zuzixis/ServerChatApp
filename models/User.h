//
// Created by Jakub Rončák on 19/12/2021.
//

#ifndef SERVER_CHATAPP_USER_H
#define SERVER_CHATAPP_USER_H

#include "iostream"
#include "Contact.h"
#include "Group.h"
#include "Message.h"
#include "Vector.h"
using namespace std;

class User {
private:
//    enum class Color { RED, BLUE, WHITE } x;
//
//    enum status {
//       AAA,BBB
//    };
    int id, port;
    string name, password, ipAddress;
    bool parIsLogged;
    vector<Message*>* messages;
    vector<Contact*>* contacts;
    vector<Group*>* groups;

public:
    User(int id, const string &name, const string &password);

    //Getter, Setter
    int getId() const;

    void setId(int id);

    int getPort() const;

    void setPort(int port);

    const string &getName() const;

    void setName(const string &name);

    const string &getPassword() const;

    void setPassword(const string &password);

    const string &getIpAddress() const;

    void setIpAddress(const string &ipAddress);

    bool isParIsLogged() const;

    void setParIsLogged(bool parIsLogged);

    vector<Message *> *getMessages() const;

    vector<Contact *> *getContacts() const;

    vector<Group *> *getGroups() const;

    // CRUD
    bool save();

    bool update();

    bool remove();
};

#endif //SERVER_CHATAPP_USER_H
