#include "Contact.h"

StatusContact* Contact::getStatus() {
    return status;
}

void Contact::setStatus(StatusContact* status) {
    Contact::status = status;
}

int Contact::getId() const {
    return id;
}

Model *Contact::get() {
    //TODO: implementovať get
    return nullptr;
}

bool Contact::save() {
    //TODO: implementovať save
    return false;
}

bool Contact::update() {
    //TODO: implementovať update
    return false;
}

bool Contact::remove(int id) {
    //TODO: implementovať remove
    return false;
}

bool Contact::exists(const int id1, const int id2) {
    json filters = json::parse(
            "{\"or\":"s + "[{\"and\":{\"user_1\":" + to_string(id1) + ",\"user_2\":" + to_string(id2) +
            "}},{\"and\":{\"user_1\":" +
            to_string(id2) + ",\"user_2\":" + to_string(id1) + "}}]}");

    json loadedContacts;
    JsonReader::read("database/contacts.json", filters, loadedContacts);
    return !loadedContacts.empty();
}
