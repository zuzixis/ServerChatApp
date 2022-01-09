


//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "ContactsController.h"

string ContactsController::getContacts(const json *data) {
    cout << *data << endl;
    int userId = ActiveUsersProvider::getInstance().getActualUserId();
    json filters = json::parse(
            R"({"or":)"s + "{\"user_1\":" + to_string(userId) + ",\"user_2\":" + to_string(userId) +
            "}}");

    json loadedContacts;
    JsonReader::read(Helpers::DATABASE_CONTACTS, filters, loadedContacts);

    json retUsers;
    if (!loadedContacts.empty()) {

        string usersFiltersString = "{\"or\":[";
        int x;
        for (auto loadedContact: loadedContacts) {
            if (loadedContact["user_1"] == userId) {
                x = loadedContact["user_2"];
            } else {
                x = loadedContact["user_1"];
            }
            usersFiltersString += ("{\"id\":" + to_string(x) + "},");
        }
        usersFiltersString = usersFiltersString.substr(0, usersFiltersString.size() - 1);
        usersFiltersString += "]}";

        cout << usersFiltersString << endl;

        json usersFilters = json::parse(usersFiltersString);
        JsonReader::read(Helpers::DATABASE_USERS, usersFilters, retUsers);
    }
    cout << retUsers << endl;
    return R"({"status": 200,"data":)" + (!retUsers.empty() ? retUsers.dump() : "[]") + "}";
}

string ContactsController::removeFromContacts(const json *data) {

    cout << *data << endl;
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    int myId = activeUsersProvider.getActualUserId();
    if (!data->contains("user_id")) {
        return R"({"status": 422,"data":{"errors":[{"user_id":"Atribút je povinný"}]}})";
    }
    int userId = data->at("user_id");

    if(!Contact::exists(myId,userId)){
        return R"({"status": 400,"data":{"errors":[{"user_id":"S týmto uživateľom neexistuje kontakt."}]}})";
    }

    json actualJson;
    JsonReader::read(Helpers::DATABASE_CONTACTS, {}, actualJson);


    if (actualJson.empty()) {
        return R"({"status": 400,"data":{"msg":""}})";
    }


    json newJson;
    copy_if(
            actualJson.begin(), actualJson.end(),
            back_inserter(newJson), [&myId, &userId](const json &item) {
                int u1 = (int) (item["user_1"]);
                int u2 = (int) (item["user_2"]);

                return !((u1 == myId && u2 == userId) || (u2 == myId && u1 == userId));

            });

    ofstream file(Helpers::DATABASE_CONTACTS);
    file << newJson;
    file.close();

    return R"({"status": 200,"data":{}})";
}