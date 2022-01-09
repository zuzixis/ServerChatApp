#pragma once

#include "User.h"
#include "Model.h"
#include "json.hpp"
#include "JsonReader.h"
#include "providers/ActiveUsersProvider.h"

class User;
class ActiveUsersProvider;


using namespace std;
using json = nlohmann::json;
enum StatusContact {
    waiting, confirmed
};


class Contact : public Model {
private:
    int id;
    const User *user1, *user2;
    StatusContact *status;

public:
    Contact() : Model() {
        id = 0;
        user1 = nullptr;
        user2 = nullptr;
        status = nullptr;
    }

    Contact(const string *file, int id, const User *user1, const User *user2, StatusContact *status) : Model(file) {
        this->id = id;
        this->user1 = user1;
        this->user2 = user2;
        this->status = status;
    };

    ~Contact() {
        //TODO:Treba implementovať, dealokovať pamat co sa vytvorilo cez new
    }

    // Gettery, Settery
    int getId() const;

    StatusContact *getStatus();

    void setStatus(StatusContact *status);

    static bool exists(int id1, int id2);

    //zdedene metody
    Model *get() override;

    bool save() override;

    bool update() override;

    bool remove(int id) override;
};
