#pragma once
#include <iostream>
#include "Group.h"
#include "User.h"
#include "Model.h"

using namespace std;
class Group;
class User;

enum Status_Message {
    sent, received, read
};

class Message : public Model{
private:
    int id;
    const Group *group_to;
    const User *user_from, *user_to;
    string message, sent_at;
    Status_Message* status;

public:
    Message() : Model(){
        id = 0;
        group_to = nullptr;
        user_from = nullptr;
        user_to = nullptr;
        message = "";
        sent_at = "";
        status = nullptr;
    }
    Message(const string *file, int id, const Group *groupTo, const User *userFrom, const User *userTo, string *message, const string *sentAt,
            Status_Message* status) : Model(file){
        this->id = id;
        this->group_to = groupTo;
        this->user_from = userFrom;
        this->user_to = userTo;
        this->message = *message;
        this->sent_at = *sentAt;
        this->status = status;
    };


    ~Message(){
        //TODO:Treba implementovať, dealokovať pamat co sa vytvorilo cez new
    }

    // Gettery, Settery
    int getId() const;
    const Group *getGroupTo() const;
    const User *getUserFrom() const;
    const User *getUserTo() const;
    string *getMessage();
    const string *getSentAt() const;
    Status_Message* getStatus() const;
    void setMessage(string *message);
    void setStatus(Status_Message* status);

    //Implementovane zdedene metody
    Model *get() override;
    bool save() override;
    bool update() override;
    bool remove(int id) override;

};