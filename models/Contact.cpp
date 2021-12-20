//
// Created by Zuzana Žillová on 19. 12. 2021.
//

#include "Contact.h"

Status_Contact* Contact::getStatus() {
    return status;
}

void Contact::setStatus(Status_Contact* status) {
    Contact::status = status;
}

Contact::Contact(int id, const User *user1, const User *user2, Status_Contact* status) : id(id), user_1(user1),
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

Group *Contact::get() {
    return nullptr;
}
