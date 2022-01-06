#include "User.h"
//
// Created by Jakub Rončák on 19/12/2021.
//

int User::getId() const {
    return id;
}

void User::setId(int id) {
    User::id = id;
}

const string &User::getName() const {
    return name;
}

void User::setName(const string &name) {
    User::name = name;
}
//
//vector<Message *> *User::getMessages() const {
//    return messages;
//}

vector<Contact *> *User::getContacts() const {
    return contacts;
}

vector<Group *> *User::getGroups() const {
    return groups;
}

//Model *User::get() {
//    //TODO:implementacia get
//    return nullptr;
//}
//
//bool User::save() {
//    //TODO:implementacia save
//    return false;
//}
//
//bool User::update() {
//    //TODO:implementacia update
//    return false;
//}
//
//bool User::remove(int id) {
//    //TODO:implementacia remove
//    return false;
//}

//void User::setMessages(vector<Message *> *messages) {
//    User::messages = messages;
//}

void User::setContacts(vector<Contact *> *contacts) {
    User::contacts = contacts;
}

//const sockaddr_in &User::getAddress() const {
//    return address;
//}
//
//void User::setAddress(const sockaddr_in &address) {
//    User::address = address;
//}

int User::getSockfd() const {
    return sockfd;
}

void User::setSockfd(int sockfd) {
    User::sockfd = sockfd;
}

void User::setGroups(vector<Group *> *groups) {
    User::groups = groups;
}

bool User::exists(const int id) {
    json loadedUsers;
    json filters = json::parse("{\"id\":" + to_string(id) + "}");
    JsonReader::read(Helpers::DATABASE_USERS, filters, loadedUsers);

    return !loadedUsers.empty();
//    if (loadedUsers.empty()) {
//        return R"({"status": 401,"data":{}})";
//    } else {
//
////    map<string, string> xx = loadedUsers.front();
//
////        map<string, string> loadedUserMap = *loadedUsers.begin();
//        // Jozko, odteraz sa odpojis od defaultnej a pojdes cez tento socket!
////        std::map<std::string, int> m2 = j;
////    User *user = new User(1, "a", *connFd);
////        cout << (typeof(loadedUsers[0]["id"])) << endl;
//        User *user = new User((int) loadedUsers[0]["id"], loadedUsers[0]["name"], *connFd);
//
//        this->activeUsersProvider->addUser(user);
//
//        return to_string((int) loadedUsers[0]["id"]);
//    }
}



