//
// Created by Jakub Rončák on 19/12/2021.
//

#include "Group.h"

Group::Group(int id, const string &name, const string &createdAt) : id(id), name(name), createdAt(createdAt) {}

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

bool Group::save() {
    return false;
}

bool Group::update() {
    return false;
}

bool Group::remove() {
    return false;
}

Model *Group::get() {
    return nullptr;
}
