//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "MessageController.h"
#include "JsonReader.h"
#include "Helpers.h"
#include "models/Group.h"

MessageController::MessageController() {

}

MessageController::~MessageController() {

}

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
        if(toId == userFrom){
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

    (*data)["user_from"] = userFrom;
    // TODO: dories status a sent_at
    (*data)["status"] = "";
    (*data)["created_at"] = Helpers::currentDateTime();

//    string message = "{"
//                     "    \"id\": 1,\n"
//                     "    \"user_from\": 1,\n"
//                     "    \"user_to\": 3,\n"
//                     "    \"group_to\": null,\n"
//                     "    \"message\": \"Celkom to ujde\",\n"
//                     "    \"status\": \"sent\",\n"
//                     "    \"sent_at\": \"2021-12-19 21:05:00\"\n"
//                     "  }";

    cout << *data << endl;
    loadedMessages.push_back(*data);
    ofstream file(Helpers::DATABASE_MESSAGES);
    file << loadedMessages;
    file.close();

    string broadJsonString = "{\"type\":" + to_string(toGroup ? 2 : 1) + ",\"data\":" + data->dump() + "}";
//    cout << "broadJsonString" << broadJsonString <<endl;
//    json broadJson = json::parse(broadJsonString);
    if (toGroup) {
        for (auto u: Group::getMembers(toId)) {
            if(u["user_id"] == userFrom){
                continue;
            }
            Helpers::broadcastToUser(u["user_id"], broadJsonString);
        }
    } else {
        Helpers::broadcastToUser(toId, broadJsonString);
    }
// TODO: ak posielam spravu do skupiny, chcem poslat upozornenie vsetkym v skupine

    return R"({"status": 200,"data":{}})";
}

string MessageController::sendFile(const json *data) {
    return "false";
}

string MessageController::sendImage(const json *data) {
    return "false";
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

// TODO: ideme davat do usera spravy?

    cout << loadedMessages << endl;
    return R"({"status": 200,"data":)" + (!loadedMessages.empty() ? loadedMessages.dump() : "[]") + "}";
}
