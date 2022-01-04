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
        return R"({"status": 401,"data":{}})";
    } else {

//    map<string, string> xx = loadedUsers.front();

//        map<string, string> loadedUserMap = *loadedUsers.begin();
        // Jozko, odteraz sa odpojis od defaultnej a pojdes cez tento socket!
//        std::map<std::string, int> m2 = j;
//    User *user = new User(1, "a", *connFd);
//        cout << (typeof(loadedUsers[0]["id"])) << endl;
        User *user = new User((int) loadedUsers[0]["id"], loadedUsers[0]["name"], *connFd);

        this->activeUsersProvider->addUser(user);

        int id = loadedUsers[0]["id"];
        return R"({"status": 200,"data":{"id":)" + to_string(id) + "}}";
    }
}

string AuthController::logout(const json *data) {
//    this->activeUsersProvider->removeUser(user);
    return "false";
}

string AuthController::deleteAccount(const json *data) {
    json loadedUsers, newJson = json::parse("[]");
    JsonReader::read("database/users.json", {}, loadedUsers);

    cout << *data << endl << endl;
    cout << loadedUsers << endl << endl;
    int id = data->at("id");
    cout << "id: " << id << endl << endl;
    bool found = false;

    copy_if(
            loadedUsers.begin(), loadedUsers.end(),
            back_inserter(newJson), [&id, &found](const json &item) {
                if ((int) (item["id"]) != id) {
                    return true;
                }
                found = true;
                return false;
//                return (int) (item["id"]) != id;
            });

    cout << newJson << endl << endl;

    if (found) {
        ofstream file("database/users.json");
        file << newJson;
        file.close();
        return R"({"status": 200,"data":{}})";

    } else {
        return R"({"status": 400,"data":{}})"; // TODO: aka tu ma byt chyba?
    }

}

string AuthController::createAccount(json *data) {
    json loadedUsers;
    JsonReader::read("database/users.json", {}, loadedUsers);

    for (auto user: loadedUsers) {
        if (user["name"] == data->at("name")) {
            return R"({"status": 409,"data":{}})";
        }
    }

    if (loadedUsers.empty()) {
        (*data)["id"] = 1;
    } else {
        cout << loadedUsers.back().at("id") << endl;
        (*data)["id"] = (int) loadedUsers.back().at("id") + 1;
    }

    loadedUsers.push_back(*data);
    ofstream file("database/users.json");
    file << loadedUsers;
    file.close();
    return R"({"status": 200,"data":{}})";
}