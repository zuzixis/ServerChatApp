
//
// Created by Zuzana Žillová on 19. 12. 2021.
//

#ifndef SERVER_CHATAPP_MESSAGE_H
#define SERVER_CHATAPP_MESSAGE_H

#include "iostream"
#include "Group.h"
#include "User.h"

enum Status_Message { sent, received, read };

using namespace std;

class Message {
private:
    int id;
    Group* group_to;
    User* user_from,*user_to;
    string message,sent_at;
    Status_Message status;


public:
    Message(int id, Group *groupTo, User *userFrom, User *userTo, const string &message, const string &sentAt,
            Status_Message status);


    // Get, Set
    int getId() const;

    Group *getGroupTo() const;

    User *getUserFrom() const;

    User *getUserTo() const;

    const string &getMessage() const;

    const string &getSentAt() const;

    Status_Message getStatus() const;

    void setMessage(const string &message);

    void setStatus(Status_Message status);

    // CRUD
    bool save();
    bool update();
    bool remove();
};


#endif //SERVER_CHATAPP_MESSAGE_H
