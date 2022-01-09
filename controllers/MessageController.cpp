//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "MessageController.h"
#include "JsonReader.h"
#include "Helpers.h"
#include "models/Group.h"


string MessageController::sendMessage(json *data) {
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();

    // Idem vytvorit spravu, ulozit ju do suboru a neskor ju poslem klientom

    if (!data->contains("message") && ((!data->contains("user_to") && !data->contains("group_to")) ||
                                       (data->contains("user_to") && data->contains("group_to")))) {
        return R"({"status": 422,"data":{}})";
    }
    bool toGroup = data->contains("group_to");
    int userFrom = activeUsersProvider.getActualUserId();
    int toId;
    if (toGroup) {
        toId = data->at("group_to");
        (*data)["user_to"] = "null";
    } else {
        toId = data->at("user_to");
        (*data)["group_to"] = "null";
        if (toId == userFrom) {
            return R"({"status": 422,"data":{}})";
        }
    }

    json loadedMessages;
    JsonReader::read(Helpers::DATABASE_MESSAGES, {}, loadedMessages);

    if (loadedMessages.empty()) {
        (*data)["id"] = 1;
    } else {
        cout << loadedMessages.back().at("id") << endl;
        (*data)["id"] = (int) loadedMessages.back().at("id") + 1;
    }

    string msg = (*data)["message"];
    string str("HELLO");
    for (int i = 0; i < str.size(); i++) {
        cout << str[i];
    }

    (*data)["user_from"] = userFrom;
    // TODO: dories status a sent_at
    (*data)["status"] = "";
    (*data)["created_at"] = Helpers::currentDateTime();

    cout << *data << endl;
    loadedMessages.push_back(*data);
    ofstream file(Helpers::DATABASE_MESSAGES);
    file << loadedMessages;
    file.close();

    json users;
    string userFiltersString = "{\"id\":" + to_string(userFrom) + "}";
    JsonReader::read(Helpers::DATABASE_USERS, json::parse(userFiltersString), users);

    (*data)["user"] = users[0];

    string broadJsonString = "{\"type\":" + to_string(toGroup ? 2 : 1) + ",\"data\":" + data->dump() + "}";
    if (toGroup) {
        for (auto u: Group::getMembers(toId)) {
            if (u["user_id"] == userFrom) {
                continue;
            }
            Helpers::broadcastToUser(u["user_id"], broadJsonString);
        }
    } else {
        Helpers::broadcastToUser(toId, broadJsonString);
    }

    return R"({"status": 200,"data":{}})";
}

json MessageController::getConversation(const json *data) {
    cout << *data << endl;
    int userFrom = ActiveUsersProvider::getInstance().getActualUserId();

    if ((data->contains("user_to") && data->contains("group_to")) ||
        (!data->contains("user_to") && !data->contains("group_to"))) {
        return R"({"status": 422,"data":{"message":"Požiadavka musí obsahovať user_to alebo group_to. Nie však obe naraz!"}})";
    }

    bool isGroup = data->contains("group_to");
    int toId;
    if (isGroup) {
        toId = data->at("group_to");
    } else {
        toId = data->at("user_to");
    }
    json filters;
    if (isGroup) {
        filters = json::parse("{\"group_to\":" + to_string(toId) + "}");
    } else {
        filters = json::parse(
                "{\"or\":"s + "[{\"and\":{\"user_from\":" + to_string(userFrom) + ",\"user_to\":" + to_string(toId) +
                "}},{\"and\":{\"user_from\":" +
                to_string(toId) + ",\"user_to\":" + to_string(userFrom) + "}}]}");
    }

    json loadedMessages;
    JsonReader::read(Helpers::DATABASE_MESSAGES, filters, loadedMessages);

    json users;
    string userFiltersString;

    for (auto &msg: loadedMessages) {
        int x = msg["user_from"];
        userFiltersString = "{\"id\":" + to_string(x) + "}";
        JsonReader::read(Helpers::DATABASE_USERS, json::parse(userFiltersString), users);

        msg["user"] = users[0];
        users.clear();
    }

    return R"({"status": 200,"data":)" + (!loadedMessages.empty() ? loadedMessages.dump() : "[]") + "}";
}

json MessageController::getMessageById(const json *data) {
    cout << *data << endl;

    if (!(data->contains("message_Id"))) {
        return R"({"status": 422,"data":{"message":"Požiadavka musí obsahovať message_Id!"}})";
    }

    int toId;
    toId = data->at("message_Id");
    json filters;

    filters = json::parse("{\"id\":" + to_string(toId) + "}");


    cout << "filters" << filters << endl;
    json loadedMessages;
    JsonReader::read(Helpers::DATABASE_MESSAGES, filters, loadedMessages);

    json users;
    string userFiltersString;

    for (auto &msg: loadedMessages) {
        int x = msg["user_from"];
        userFiltersString = "{\"id\":" + to_string(x) + "}";
        JsonReader::read(Helpers::DATABASE_USERS, json::parse(userFiltersString), users);

        msg["user"] = users[0];
        users.clear();
    }

    cout << loadedMessages << endl;
    return R"({"status": 200,"data":)" + (!loadedMessages.empty() ? loadedMessages.dump() : "[]") + "}";

}
