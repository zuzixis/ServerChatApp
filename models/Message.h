#pragma once

//
// Created by Zuzana Žillová on 19. 12. 2021.
//

#include "iostream"
#include "Group.h"
#include "User.h"
#include "Model.h"

using namespace std;


enum Status_Message {
    sent, received, read
};

class Message : Model {
private:
    int id;
    const Group *group_to;
    const User *user_from, *user_to;
    string *message;
    const string *sent_at;
    Status_Message *status;


public:
    Message(int id, const Group *groupTo, const User *userFrom, const User *userTo, string *message,
            const string *sentAt,
            Status_Message *status);


    // Get, Set
    int getId() const;

    const Group *getGroupTo() const;

    const User *getUserFrom() const;

    const User *getUserTo() const;

    string *getMessage();

    const string *getSentAt() const;

    Status_Message *getStatus() const;

    void setMessage(string *message);

    void setStatus(Status_Message *status);

    // CRUD
    static Model* get();

    bool save();

    bool update();

    bool remove();
};
