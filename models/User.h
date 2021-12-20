#pragma once
#include "Contact.h"
#include "Message.h"
#include <vector>
#include <iostream>

//
// Created by Jakub Rončák on 19/12/2021.
//

class Contact;
class Message;

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
    User(){
        id = 0;
        port = 0;
        name = "";
        password = "";
        ipAddress = "";
        parIsLogged = false;
        messages = nullptr;
        contacts = nullptr;
        groups = nullptr;
    }
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
