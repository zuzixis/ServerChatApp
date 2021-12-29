#pragma once

#include "Contact.h"
//#include "Message.h"
#include <utility>
#include <vector>
#include <iostream>
#include "Model.h"
#include "../json.hpp"
#include <netinet/in.h>

class Contact;
class Message;
class Group;
//using json = nlohmann::json;
using namespace std;

class User{//; : public Model {
private:
    int id;
//    , port;
    string name;//, password, ipAddress;
//    bool parIsLogged;
//    sockaddr_in activeSocket{};
//    string token;
//    vector<Message *> *messages;
    vector<Contact *> *contacts;
//    struct sockaddr_in address;
    int sockfd;
    vector<Group *> *groups;

public:
    User() {//: Model() {
        id = 0;
        name = "";
//        address = {};
        sockfd = 0;
//        parIsLogged = false;
//        messages = nullptr;
        contacts = nullptr;
        groups = nullptr;
    }

//    User(const json& json){
//        cout << json;
//    }

    User(int id, string name,int sockfd) {
        this->id = id;
        this->name = std::move(name); // todo: move alebo copy?
//        this->address = address;
        this->sockfd = sockfd;

        //TODO: dopln tu tieto hodnoty
//        this->messages = nullptr;
        this->contacts = nullptr;
        this->groups = nullptr;
    }

    /*User(int id, const string &name, const string &password) {
        this->id = id;

    };*/

    ~User() {
        //TODO:Treba implementovať, dealokovať pamat co sa vytvorilo cez new
    }

    //Getter, Setter
    int getId() const;

    void setId(int id);

//    int getPort() const;
//
//    void setPort(int port);

    const string &getName() const;

    void setName(const string &name);

//    void setMessages(vector<Message *> *messages);

    void setContacts(vector<Contact *> *contacts);

//    const sockaddr_in &getAddress() const;

//    void setAddress(const sockaddr_in &address);

    int getSockfd() const;

    void setSockfd(int sockfd);

    void setGroups(vector<Group *> *groups);
//    const string &getPassword() const;
//
//    void setPassword(const string &password);
//
//    const string &getIpAddress() const;
//
//    void setIpAddress(const string &ipAddress);

//    bool isParIsLogged() const;

//    void setParIsLogged(bool parIsLogged);

    vector<Message *> *getMessages() const;

    vector<Contact *> *getContacts() const;

    vector<Group *> *getGroups() const;

//    //zdedene metody
//    Model *get() override;
//
//    bool save() override;
//
//    bool update() override;
//
//    bool remove(int id) override;

};
