#include "iostream"

//
// Created by Jakub Rončák on 19/12/2021.
//

#ifndef SERVER_CHATAPP_GROUP_H
#define SERVER_CHATAPP_GROUP_H

using namespace std;

class Group {
private:
    int id;
    string name, createdAt;

public:
    Group(int id, const string &name, const string &createdAt);

    //Getter, Setter
    int getId() const;

    void setId(int id);

    const string &getName() const;

    void setName(const string &name);

    const string &getCreatedAt() const;

    void setCreatedAt(const string &createdAt);

    //CRUD
    bool save();

    bool update();

    bool remove();

};


#endif //SERVER_CHATAPP_GROUP_H
