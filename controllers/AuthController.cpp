#include "AuthController.h"

AuthController::AuthController(ActiveUsersProvider *activeUsersProvider) {
    this->activeUsersProvider = activeUsersProvider;
}

AuthController::~AuthController() {

}

string AuthController::login(const json *data, int *connFd) {
    json loadedUsers;
    JsonReader::read("database/users.json", *data, loadedUsers);

    if (loadedUsers.empty()) {
        return R"({"status": "401","data":{}})";
    } else {

//    map<string, string> xx = loadedUsers.front();

//        map<string, string> loadedUserMap = *loadedUsers.begin();
        // Jozko, odteraz sa odpojis od defaultnej a pojdes cez tento socket!
//        std::map<std::string, int> m2 = j;
//    User *user = new User(1, "a", *connFd);
//        cout << (typeof(loadedUsers[0]["id"])) << endl;
        User *user = new User((int) loadedUsers[0]["id"], loadedUsers[0]["name"], *connFd);

        this->activeUsersProvider->addUser(user);

        return to_string((int)loadedUsers[0]["id"]);
    }
}

string AuthController::logout(const json *data) {
//    this->activeUsersProvider->removeUser(user);
    return "false";
}

string AuthController::deleteAccount(const json *data) {
    return "false";
}

string AuthController::createAccount(map<string, string> *data) {
    json loadedUsers;
    JsonReader::read("database/users.json", {}, loadedUsers);

    (*data)["id"] = to_string(loadedUsers.size() + 1);
    // TODO: mozeme takto generovat id pokial nejdeme pouzivat deleteAccount
    loadedUsers.push_back(*data);
    ofstream file("database/users.json");
    file << loadedUsers;
    file.close();
    return "false";
}