//
// Created by Zuzana Žillová on 19. 12. 2021.
//

#include "Message.h"

Message::Message(int id, Group *groupTo, User *userFrom, User *userTo, const string &message, const string &sentAt,
                 Status_Message status) : id(id), group_to(groupTo), user_from(userFrom), user_to(userTo),
                                          message(message), sent_at(sentAt), status(status) {}

int Message::getId() const {
    return id;
}

Group *Message::getGroupTo() const {
    return group_to;
}

User *Message::getUserFrom() const {
    return user_from;
}

User *Message::getUserTo() const {
    return user_to;
}

const string &Message::getMessage() const {
    return message;
}

const string &Message::getSentAt() const {
    return sent_at;
}

Status_Message Message::getStatus() const {
    return status;
}

void Message::setMessage(const string &message) {
    Message::message = message;
}

void Message::setStatus(Status_Message status) {
    Message::status = status;
}

bool Message::save() {
    return false;
}

bool Message::update() {
    return false;
}

bool Message::remove() {
    return false;
}
