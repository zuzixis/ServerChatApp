#include "Contact.h"
//
// Created by Zuzana Žillová on 19. 12. 2021.
//

StatusContact* Contact::getStatus() {
    return status;
}

void Contact::setStatus(StatusContact* status) {
    Contact::status = status;
}

Contact::Contact(int id, const User *user1, const User *user2, StatusContact* status) : id(id), user_1(user1),
                                                                                         user_2(user2), status(status) {}

bool Contact::save() {
    return false;
}

bool Contact::update() {
    return false;
}

bool Contact::remove() {
    return false;
}

int Contact::getId() const {
    return id;
}