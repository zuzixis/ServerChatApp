#include "AuthController.h"

AuthController::AuthController(ActiveUsersProvider *activeUsersProvider) {
    this->activeUsersProvider = activeUsersProvider;
}

AuthController::~AuthController() {

}

map<string, string> AuthController::login(const map<string, string> *data, int *connFd) {
    json loadedUsers;
    JsonReader::read("database/users.json", *data, loadedUsers);

//    if (loadedUsers.empty()) {
//        return {{"status", "401"}};
//    } else {

//    map<string, string> xx = loadedUsers.front();

//        map<string, string> loadedUserMap = *loadedUsers.begin();
    // Jozko, odteraz sa odpojis od defaultnej a pojdes cez tento socket!
//        std::map<std::string, int> m2 = j;
//    User *user = new User(1, "a", *connFd);
        User *user = new User((int)loadedUsers[0]["id"], loadedUsers[0]["name"], *connFd);

    this->activeUsersProvider->addUser(user);

    return {{"status", "200"}};
//    }
}

bool AuthController::logout(const User* user) {
    this->activeUsersProvider->removeUser(user);
}

bool AuthController::deleteAccount(const map<string, string> *data) {
    return false;
}

bool AuthController::createAccount(map<string, string> *data) {
    json loadedUsers;
    JsonReader::read("database/users.json", {}, loadedUsers);

    (*data)["id"] = to_string(loadedUsers.size()+1);
    // TODO: mozeme takto generovat id pokial nejdeme pouzivat deleteAccount
    loadedUsers.push_back(*data);
    ofstream file("database/users.json");
    file << loadedUsers;
    file.close();
}