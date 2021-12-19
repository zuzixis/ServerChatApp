#include "iostream"
//
// Created by Jakub Rončák on 19/12/2021.
//

#ifndef SERVER_CHATAPP_USER_H
#define SERVER_CHATAPP_USER_H

using namespace std;
class User {
private:
    int id,port;
    string name,password,ipAddress;
    bool parIsLogged;

public:
    User(int id, const string &name, const string &password);

    // Gettery
    int getId() const;
    int getPort() const;
    const string &getName() const;
    const string &getPassword() const;
    const string &getIpAddress() const;
    bool isLogged() const;

    // Settery
//    void setId(int id);
    void setPort(int port);
    void setName(const string &name);
    void setPassword(const string &password);
    void setIpAddress(const string &ipAddress);
    void setParIsLogged(bool parIsLogged);

    // CRUD
    bool save();
    bool update();
    bool remove();
};


#endif //SERVER_CHATAPP_USER_H
