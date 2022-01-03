//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "MessageController.h"
#include "../JsonReader.h"
#include "../Helpers.h"

MessageController::MessageController() {

}

MessageController::~MessageController() {

}

string MessageController::sendMessage(json *data) {
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    int from = activeUsersProvider.getActualUserId();

    // Idem vytvorit spravu, ulozit ju do suboru a neskor ju poslem klientom

    if (!data->contains("message") && (!data->contains("user_to") || !data->contains("group_to"))) {
        return R"({"status": 422,"data":{}})";
    }

    json loadedMessages;
    JsonReader::read("database/messages.json", {}, loadedMessages);

    if (loadedMessages.empty()) {
        (*data)["id"] = 1;
    } else {
        cout << loadedMessages.back().at("id") << endl;
        (*data)["id"] = (int) loadedMessages.back().at("id") + 1;
    }


    (*data)["user_from"] = from;
    // TODO: dories status a sent_at
    (*data)["status"] = "";
    (*data)["sent_at"] = "";

//    string message = "{"
//                     "    \"id\": 1,\n"
//                     "    \"user_from\": 1,\n"
//                     "    \"user_to\": 3,\n"
//                     "    \"group_to\": null,\n"
//                     "    \"message\": \"Celkom to ujde\",\n"
//                     "    \"status\": \"sent\",\n"
//                     "    \"sent_at\": \"2021-12-19 21:05:00\"\n"
//                     "  }";

cout<<*data<<endl;
    loadedMessages.push_back(*data);
    ofstream file("database/messages.json");
    file << loadedMessages;
    file.close();
    vector<User *> acceptorConnections = activeUsersProvider.getById(data->at("user_to"));
//    // TODO: activeUsersProvider sa moze skor vola ActiveConnectionsProvider a tam by bol user a fd

    char buffer[2048];
    string message = data->dump();
    for (auto &userConnection: acceptorConnections) // access by reference to avoid copying
    {
        bzero(buffer, 2048);
        Helpers::sgets(buffer, 2048, &message);
        send(userConnection->getSockfd(), buffer, 2048, 0);
    }
    return R"({"status": 200,"data":{}})";
// TODO: user nemusi byt prihlaseny, teda musim si danu spravu ulozit do suboru a aj do premennej.
//  V subore budu vsetky spravy aj s priznakom, ci uz boli precitane
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
    int userTo = data->at("user_to");

    json filters = json::parse(
            "{\"or\":"s + "[{\"and\":{\"user_from\":" + to_string(userFrom) + ",\"user_to\":" + to_string(userTo) +
            "}},{\"and\":{\"user_from\":" +
            to_string(userTo) + ",\"user_to\":" + to_string(userFrom) + "}}]}");


    json loadedMessages;
    JsonReader::read("database/messages.json", filters, loadedMessages);

//    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
// TODO: ideme davat do usera spravy?

//    return user->getMessages();
    cout << loadedMessages << endl;
    return R"({"status": 200,"data":)" + loadedMessages.dump() + "}";
//    return loadedMessages;
}
