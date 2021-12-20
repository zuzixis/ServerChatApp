#pragma once
#include "Contact.h"
#include "Message.h"
#include <vector>
#include <iostream>
#include "Model.h"

class Contact;
class Message;
class Group;
using namespace std;

class User : private Model{
private:
    int id, port;
    string name, password, ipAddress;
    bool parIsLogged;
    vector<Message*>* messages;
    vector<Contact*>* contacts;
    vector<Group*>* groups;

public:
    User() : Model(){
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

    User(const string *file, int id, int port, const string &name, const string &password, const string &ipAddress) : Model(file){
        this->id = id;
        this->port = port;
        this->name = name;
        this->password = password;
        this->ipAddress = ipAddress;
    }

    /*User(int id, const string &name, const string &password) {
        this->id = id;

    };*/

    ~User(){
        //TODO:Treba implementovať, dealokovať pamat co sa vytvorilo cez new
    }

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

    //zdedene metody
    Model *get() override;
    bool save() override;
    bool update() override;
    bool remove(int id) override;
};
