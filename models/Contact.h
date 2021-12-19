//
// Created by Zuzana Žillová on 19. 12. 2021.
//

#ifndef SERVER_CHATAPP_CONTACT_H
#define SERVER_CHATAPP_CONTACT_H

#include "User.h"

enum Status_Message {
    waiting, confirmed
};

class Contact {
    int id;
    User *user_1, *user_2;
    Status_Message *status;

public:
    Contact(int id, const User &user1, const User &user2, Status_Message status);

    // Get, Set
    Status_Message getStatus() const;

    void setStatus(Status_Message status);

    // CRUD
    bool save();

    bool update();

    bool remove();
};


#endif //SERVER_CHATAPP_CONTACT_H
