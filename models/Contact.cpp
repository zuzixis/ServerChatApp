//
// Created by Zuzana Žillová on 19. 12. 2021.
//

#include "Contact.h"

Status_Message Contact::getStatus() const {
    return status;
}

void Contact::setStatus(Status_Message status) {
    Contact::status = status;
}

Contact::Contact(int id, const User &user1, const User &user2, Status_Message status) : id(id), user_1(user1),
                                                                                        user_2(user2), status(status) {}
