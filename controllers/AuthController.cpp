#include "AuthController.h"

AuthController::AuthController(ActiveUsersProvider *activeUsersProvider) {
    this->activeUsersProvider = activeUsersProvider;
}

AuthController::~AuthController() {

}

map<string, string> AuthController::login(const map<string, string> *data, int *connFd) {
    json loadedUsers;
//    JsonReader::read("database/users.json", *data, loadedUsers);

//    if (loadedUsers.empty()) {
//        return {{"status", "401"}};
//    } else {

//    map<string, string> xx = loadedUsers.front();

//        map<string, string> loadedUserMap = *loadedUsers.begin();
    // Jozko, odteraz sa odpojis od defaultnej a pojdes cez tento socket!
//        std::map<std::string, int> m2 = j;
    User *user = new User(1, "a", *connFd);
//        User *user = new User(stoi(loadedUser.get<string>("id")), loadedUser["name"], *connFd);

    this->activeUsersProvider->addUser(user);



    // TODO: tu treba vytvorit spojenie s userom na zaklade aktualneho socketu a jeho instanciu si ulozit
    //  v modeli. Tam nam asi netreba ip ani port, ale skor ten socket, ked budeme aj niekoho kontaktovat,
    //  ze mu prisla sprava. Takisto treba zmenit status v modeli. Kde si ulozim tento model? Vratim ho spat
    //  a v maine urobim nove vlakno pre neho alebo dame osobitnu triedu, kde bude vektor aktivnych userov?

    return {{"status", "200"}};
//    }
}

bool AuthController::logout(const map<string, string> *data) {
    return false;
}

bool AuthController::deleteAccount(const map<string, string> *data) {
    return false;
}

bool AuthController::createAccount(const map<string, string> *data) {
    return false;
}