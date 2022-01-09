#include "AuthController.h"

AuthController::AuthController(ActiveUsersProvider *activeUsersProvider) {
    this->activeUsersProvider = activeUsersProvider;
}

string AuthController::login(const json *data, int *connFd) {
    json loadedUsers;
    JsonReader::read(Helpers::DATABASE_USERS, *data, loadedUsers);
    cout << loadedUsers << endl;
    if (loadedUsers.empty()) {
        return R"({"status": 401,"data":{"msg":"Zlé prihlásovacie údaje."}})";
    } else {
        if (ActiveUsersProvider::getInstance().getActualUserId() > 0) {
            return R"({"status": 401,"data":{"msg":"Už ste prihlásený."}})";
        }

        User *user = new User((int) loadedUsers[0]["id"], loadedUsers[0]["name"], *connFd);

        this->activeUsersProvider->addUser(user);
        int id = loadedUsers[0]["id"];
        return to_string(id);
    }
}

string AuthController::logout(const json *data) {
    return "false";
}

string AuthController::deleteAccount(const json *data) {
    json loadedJson, newJson;
    JsonReader::read(Helpers::DATABASE_USERS, {}, loadedJson);

    cout << *data << endl << endl;
    cout << loadedJson << endl << endl;

    int id = ActiveUsersProvider::getInstance().getActualUserId();
    bool found = false;

    copy_if(
            loadedJson.begin(), loadedJson.end(),
            back_inserter(newJson), [&id, &found](const json &item) {
                if ((int) (item["id"]) != id) {
                    return true;
                }
                found = true;
                return false;
            });

    cout << newJson << endl << endl;

    if (found) {
        ofstream fileUsers(Helpers::DATABASE_USERS);
        fileUsers << newJson;
        fileUsers.close();

        loadedJson.clear();
        JsonReader::read(Helpers::DATABASE_MESSAGES, {}, loadedJson);
        newJson.clear();
        copy_if(
                loadedJson.begin(), loadedJson.end(),
                back_inserter(newJson), [&id](const json &item) {
                    return !((int) (item["user_from"]) == id ||
                             (item["user_to"] != "null" && (int) (item["user_to"]) != id));
                });

        ofstream fileMessages(Helpers::DATABASE_MESSAGES);
        fileMessages << newJson;
        fileMessages.close();

        loadedJson.clear();
        JsonReader::read(Helpers::DATABASE_CONTACT_REQUESTS, {}, loadedJson);
        newJson.clear();
        copy_if(
                loadedJson.begin(), loadedJson.end(),
                back_inserter(newJson), [&id](const json &item) {
                    if ((int) (item["user_from"]) != id && (int) (item["user_to"]) != id) {
                        return true;
                    }
                    return false;
                });

        ofstream fileRequests(Helpers::DATABASE_CONTACT_REQUESTS);
        fileRequests << newJson;
        fileRequests.close();

        loadedJson.clear();
        JsonReader::read(Helpers::DATABASE_CONTACTS, {}, loadedJson);
        newJson.clear();
        copy_if(
                loadedJson.begin(), loadedJson.end(),
                back_inserter(newJson), [&id](const json &item) {
                    if ((int) (item["user_1"]) != id && (int) (item["user_2"]) != id) {
                        return true;
                    }
                    return false;
                });

        ofstream fileContacts(Helpers::DATABASE_CONTACTS);
        fileContacts << newJson;
        fileContacts.close();

        loadedJson.clear();
        JsonReader::read(Helpers::DATABASE_GROUP_USERS, {}, loadedJson);
        newJson.clear();
        copy_if(
                loadedJson.begin(), loadedJson.end(),
                back_inserter(newJson), [&id](const json &item) {
                    if ((int) (item["user_id"]) != id) {
                        return true;
                    }
                    return false;
                });

        ofstream fileGroupUsers(Helpers::DATABASE_GROUP_USERS);
        fileGroupUsers << newJson;
        fileGroupUsers.close();

        return R"({"status": 200,"data":{}})";
    } else {
        return R"({"status": 400,"data":{"msg":""}})";
    }
}

string AuthController::createAccount(json *data) {
    json loadedUsers;
    JsonReader::read(Helpers::DATABASE_USERS, {}, loadedUsers);

    if (!data->contains("name")) {
        return R"({"status": 422,"data":{"errors":[{"name":"Názov je povinný"}]}})";
    }

    for (auto user: loadedUsers) {
        if (user["name"] == data->at("name")) {
            return R"({"status": 409,"data":{"msg":"Uživateľ s takýmto menom už je zaregistrovaný"}})";
        }
    }

    if (loadedUsers.empty()) {
        (*data)["id"] = 1;
    } else {
        cout << loadedUsers.back().at("id") << endl;
        (*data)["id"] = (int) loadedUsers.back().at("id") + 1;
    }

    loadedUsers.push_back(*data);
    ofstream file(Helpers::DATABASE_USERS);
    file << loadedUsers;
    file.close();
    return R"({"status": 200,"data":{}})";
}