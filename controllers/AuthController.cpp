#include "AuthController.h"

AuthController::AuthController() {

}

AuthController::~AuthController() {

}

map<string, string> AuthController::login(const map<string, string> *data) {
    map<string, string> loadedUser = JsonReader::read("database/users.json", *data);
    if (loadedUser.empty()) {
        return {{"status", "401"}};
    } else {

//        User *user = new User("", loadedUser["id"], int port, const string &ipAddress);
        // TODO: tu treba vytvorit spojenie s userom na zaklade aktualneho socketu a jeho instanciu si ulozit
        //  v modeli. Tam nam asi netreba ip ani port, ale skor ten socket, ked budeme aj niekoho kontaktovat,
        //  ze mu prisla sprava. Takisto treba zmenit status v modeli. Kde si ulozim tento model? Vratim ho spat
        //  a v maine urobim nove vlakno pre neho alebo dame osobitnu triedu, kde bude vektor aktivnych userov?

        return {{"status","200"}};
    }
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