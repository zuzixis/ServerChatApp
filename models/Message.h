#pragma once


//
// Created by Zuzana Žillová on 19. 12. 2021.
//

#include <iostream>
#include "Group.h"
#include "User.h"

class User;
class Group;

using namespace std;


enum Status_Message {
    sent, received, read
};

class Message {
private:
    int id;
    const Group *group_to;
    const User *user_from, *user_to;
    string message, sent_at;
    Status_Message* status;


public:
    Message(){
        id = 0;
        group_to = nullptr;
        user_from = nullptr;
        user_to = nullptr;
        message = "";
        sent_at = "";
        status = nullptr;
    }
    Message(int id, const Group *groupTo, const User *userFrom, const User *userTo, string *message, const string *sentAt,
            Status_Message* status);


    // Get, Set
    int getId() const;

    const Group *getGroupTo() const;

    const User *getUserFrom() const;

    const User *getUserTo() const;

    string *getMessage();

    const string *getSentAt() const;

    Status_Message* getStatus() const;

    void setMessage(string *message);

    void setStatus(Status_Message* status);

    // CRUD
    bool save();

    bool update();

    bool remove();
};