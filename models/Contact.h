#pragma once

//
// Created by Zuzana Žillová on 19. 12. 2021.
//


#include "User.h"
#include "Model.h"

enum Status_Contact {
    waiting, confirmed
};

class Contact : Model {
    int id;
    const User *user_1, *user_2;
    Status_Contact *status;

public:
    Contact(int id, const User *user1, const User *user2, Status_Contact *status);

    // Get, Set
    int getId() const;

    Status_Contact *getStatus();

    void setStatus(Status_Contact *status);

    // CRUD
    static Model* get();

    bool save();

    bool update();

    bool remove();
};

