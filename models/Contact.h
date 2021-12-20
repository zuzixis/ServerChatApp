#pragma once
#include "User.h"

//
// Created by Zuzana Žillová on 19. 12. 2021.
//


class User;

enum StatusContact {
    waiting, confirmed
};

class Contact {
    int id;
    const User *user_1, *user_2;
    StatusContact *status;

public:
    Contact(){
        id = 0;
        user_1 = nullptr;
        user_2 = nullptr;
        status = nullptr;
    }
    Contact(int id, const User* user1, const User* user2, StatusContact* status);

    // Get, Set
    int getId() const;

    StatusContact* getStatus();

    void setStatus(StatusContact* status);

    // CRUD
    bool save();

    bool update();

    bool remove();
};
