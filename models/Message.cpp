#include "Message.h"
/*Message::Message(int id, const Group *groupTo, const User *userFrom, const User *userTo, string *message,
                 const string *sentAt,
                 Status_Message *status) : id(id), group_to(groupTo), user_from(userFrom), user_to(userTo),
                                           status(status) {
    // TODO: dorobit konstruktor stringov - ????
}*/

int Message::getId() const {
    return id;
}

const Group *Message::getGroupTo() const {
    return group_to;
}

const User *Message::getUserFrom() const {
    return user_from;
}


const User *Message::getUserTo() const {
    return user_to;
}

string *Message::getMessage() {
    return &message;
}

const string *Message::getSentAt() const {
    return &sent_at;
}

Status_Message* Message::getStatus() const {
    return status;
}

void Message::setMessage(string *message) {
    this->message = (*message);
}

void Message::setStatus(Status_Message* status) {
    Message::status = status;
}

Model *Message::get() {
    //TODO: implementovať get
    return nullptr;
}

bool Message::save() {
    //TODO: implementovať save
    return false;
}

bool Message::update() {
    //TODO: implementovať update
    return false;
}

bool Message::remove(int id) {
    //TODO: implementovať remove
    return false;
}
