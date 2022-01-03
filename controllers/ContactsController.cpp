//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "ContactsController.h"

ContactsController::ContactsController() {

}

ContactsController::~ContactsController() {

}

string ContactsController::getContacts(const json* data) {
    cout << *data << endl;
    int userId = ActiveUsersProvider::getInstance().getActualUserId();
//    int userTo = data->at("user_to");
        // {or:{x:1,y:2}}
    json filters = json::parse(
            R"({"or":)"s + "{\"user_1\":" + to_string(userId) + ",\"user_2\":" + to_string(userId) +
            "}}");

    json loadedContacts;
    JsonReader::read("database/contacts.json", filters, loadedContacts);

//    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
// TODO: ideme davat do usera spravy?

//    return user->getMessages();
    cout << loadedContacts << endl;
    return R"({"status": 200,"data":)" + loadedContacts.dump() + "}";
//    return loadedMessages;
}
