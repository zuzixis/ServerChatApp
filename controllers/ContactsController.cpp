//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "ContactsController.h"

ContactsController::ContactsController() {

}

ContactsController::~ContactsController() {

}

string ContactsController::getContacts(const json *data) {
    cout << *data << endl;
    int userId = ActiveUsersProvider::getInstance().getActualUserId();
//    int userTo = data->at("user_to");
    // {or:{x:1,y:2}}
    json filters = json::parse(
            R"({"or":)"s + "{\"user_1\":" + to_string(userId) + ",\"user_2\":" + to_string(userId) +
            "}}");

    json loadedContacts;
    JsonReader::read("database/contacts.json", filters, loadedContacts);

    json retUsers;
    string usersFiltersString = "{\"or\":[";
    int x;
    for (auto loadedContact: loadedContacts) {
        if (loadedContact["user_1"] == userId){
            x = loadedContact["user_2"];
        } else {
            x = loadedContact["user_1"];
        }
        usersFiltersString += ("{\"id\":" + to_string(x) + "},");
    }
    usersFiltersString = usersFiltersString.substr(0, usersFiltersString.size() - 1);
    usersFiltersString += "]}";

    JsonReader::read("database/users.json", usersFiltersString, retUsers);

    cout << loadedContacts << endl;
    return R"({"status": 200,"data":)" + (!retUsers.empty() ? retUsers.dump() : "[]") + "}";
}
