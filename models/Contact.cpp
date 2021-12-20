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