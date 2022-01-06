#include "Group.h"

int Group::getId() const {
    return id;
}

void Group::setId(int id) {
    Group::id = id;
}

const string &Group::getName() const {
    return name;
}

void Group::setName(const string &name) {
    Group::name = name;
}

const string &Group::getCreatedAt() const {
    return createdAt;
}

void Group::setCreatedAt(const string &createdAt) {
    Group::createdAt = createdAt;
}

Model *Group::get() {
    //TODO: Implementovat get
    return nullptr;
}

bool Group::save() {
    //TODO: Implementovat save
    return false;
}

bool Group::update() {
    //TODO: Implementovat update
    return false;
}

bool Group::remove(int id) {
    //TODO: Implementovat remove
    return false;
}

bool Group::exists(const int id) {
    json loadedUsers;
    json filters = json::parse("{\"id\":" + to_string(id) + "}");
    JsonReader::read(Helpers::DATABASE_GROUP, filters, loadedUsers);

    return !loadedUsers.empty();
}
