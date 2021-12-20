#pragma once

//
// Created by Jakub Rončák on 19/12/2021.
//

#include "iostream"
#include "Contact.h"
#include "Group.h"
#include "Message.h"
#include "vector"
#include "Model.h"

using namespace std;

class User : Model {
private:
//    enum class Color { RED, BLUE, WHITE } x;
//
//    enum status {
//       AAA,BBB
//    };
    const int id;
    int port;
    string file = "aa"; // TODO: neviem, ci model vie o hodnote vo file
    string *name, *password, *ipAddress;
    // TODO: nemozu byt smerniky vzdy const? Ja v podsate menim iba hodnotu na danej adrese
    bool parIsLogged;
    vector<Message *> *messages;
    vector<Contact *> *contacts;
    vector<Group *> *groups;

public:
    User(const string *file, const int id, string *name, string *password);

    //Getter, Setter
    int getId() const;

    void setId(int id);

    int getPort() const;

    void setPort(int port);
 // TODO: co robi const na zaciatku a co na konci?
 // TODO: aky je rozdiel medzi string & a string *?
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
    // TODO: ako sa robí správne v cpp dedičnosť?
    static Model* get();

    bool save();

    bool update();

    bool remove();
};
