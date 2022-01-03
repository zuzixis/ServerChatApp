#include "RequestsController.h"

RequestsController::RequestsController() {

}

RequestsController::~RequestsController() {

}

string RequestsController::askForRequestsContact(const json *data) {

    cout << *data << endl;
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    int userFrom = activeUsersProvider.getActualUserId();
    int userTo = data->at("user_to");

    json filters = json::parse(
            "{\"or\":"s + "[{\"and\":{\"user_1\":" + to_string(userFrom) + ",\"user_2\":" + to_string(userTo) +
            "}},{\"and\":{\"user_2\":" +
            to_string(userFrom) + ",\"user_1\":" + to_string(userTo) + "}}]}");

    json loadedContacts;
    JsonReader::read("database/contacts.json", filters, loadedContacts);

    if(!loadedContacts.empty()){
        return R"({"status": 400,"data":{}})";
    }

    json newRequest;
    newRequest["user_1"] = userFrom;
    newRequest["user_2"] = userTo;
    newRequest["status"] = "waiting";

    JsonReader::read("database/contacts.json", {}, loadedContacts);
    loadedContacts.push_back(newRequest);

    ofstream file("database/contacts.json");
    file << loadedContacts;
    file.close();

    vector<User *> acceptorConnections = activeUsersProvider.getById(data->at("user_to"));
//    // TODO: activeUsersProvider sa moze skor vola ActiveConnectionsProvider a tam by bol user a fd

    char buffer[4096];
    string message = data->dump();
    int receiveSendStatus;
    for (auto &userConnection: acceptorConnections) // access by reference to avoid copying
    {
        bzero(buffer, 4096);
        Helpers::sgets(buffer, 4096, &message);

        receiveSendStatus = send(userConnection->getSockfd(), buffer, 4096, 0);
    }

    return R"({"status": 200,"data":{}})";

//    return "false";
}

string RequestsController::getContactRequests(const json *data) {
    cout << *data << endl;
    int userId = ActiveUsersProvider::getInstance().getActualUserId();
        // {"and":{or:{x:1,y:2},status:waiting}}
    json filters = json::parse(
            R"({"and":{"or":)"s + "{\"user_1\":" + to_string(userId) + ",\"user_2\":" + to_string(userId) +
            R"(},"status":"waiting"})");

    json loadedRequests;
    JsonReader::read("database/contacts.json", filters, loadedRequests);

    cout << loadedRequests << endl;
    return R"({"status": 200,"data":)" + loadedRequests.dump() + "}";
}

string RequestsController::confirmationContactRequest(const json *data) {
    cout << *data << endl;
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    int userFrom = activeUsersProvider.getActualUserId();
    int userTo = data->at("user_to");

    json filters = json::parse(
            "{\"or\":"s + "[{\"and\":{\"user_1\":" + to_string(userFrom) + ",\"user_2\":" + to_string(userTo) +
            "}},{\"and\":{\"user_2\":" +
            to_string(userFrom) + ",\"user_1\":" + to_string(userTo) + "}}]}");

    json loadedContacts;
    JsonReader::read("database/contacts.json", filters, loadedContacts);

    if(loadedContacts.empty()){
        return R"({"status": 400,"data":{}})";
    }

    json editedRequest = loadedContacts[0];
    editedRequest["status"] = "confirmed";

    JsonReader::read("database/contacts.json", {}, loadedContacts);

//    bool found = false;
    json newJson;
    copy_if(
            loadedContacts.begin(), loadedContacts.end(),
            back_inserter(newJson), [&userFrom, &userTo](const json &item) {
                if (((int) (item["user_1"]) == userFrom && (int) (item["user_2"]) == userTo)||
                        ((int) (item["user_2"]) == userFrom && (int) (item["user_1"]) == userTo)) {
                    return true;
                }
//                found = true;
                return false;
            });
    newJson.push_back(editedRequest);

    ofstream file("database/contacts.json");
    file << newJson;
    file.close();

    vector<User *> acceptorConnections = activeUsersProvider.getById(data->at("user_to"));
//    // TODO: activeUsersProvider sa moze skor vola ActiveConnectionsProvider a tam by bol user a fd

    char buffer[4096];
    string message = editedRequest.dump();
    int receiveSendStatus;
    for (auto &userConnection: acceptorConnections) // access by reference to avoid copying
    {
        bzero(buffer, 4096);
        Helpers::sgets(buffer, 4096, &message);

        receiveSendStatus = send(userConnection->getSockfd(), buffer, 4096, 0);
    }

    return R"({"status": 200,"data":{}})";
}

string RequestsController::rejectContactRequest(const json *data) {

    cout << *data << endl;
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    int userFrom = activeUsersProvider.getActualUserId();
    int userTo = data->at("user_to");

    json filters = json::parse(
            "{\"or\":"s + "[{\"and\":{\"user_1\":" + to_string(userFrom) + ",\"user_2\":" + to_string(userTo) +
            "}},{\"and\":{\"user_2\":" +
            to_string(userFrom) + ",\"user_1\":" + to_string(userTo) + "}}]}");

    json loadedContacts;
    JsonReader::read("database/contacts.json", filters, loadedContacts);

    if(loadedContacts.empty()){
        return R"({"status": 400,"data":{}})";
    }

//    json editedRequest = loadedContacts[0];
//    editedRequest["status"] = "confirmed";

    JsonReader::read("database/contacts.json", {}, loadedContacts);

//    bool found = false;
    json newJson;
    copy_if(
            loadedContacts.begin(), loadedContacts.end(),
            back_inserter(newJson), [&userFrom, &userTo](const json &item) {
                if (((int) (item["user_1"]) == userFrom && (int) (item["user_2"]) == userTo)||
                    ((int) (item["user_2"]) == userFrom && (int) (item["user_1"]) == userTo)) {
                    return true;
                }
//                found = true;
                return false;
            });
//    newJson.push_back(editedRequest);

    ofstream file("database/contacts.json");
    file << newJson;
    file.close();

    vector<User *> acceptorConnections = activeUsersProvider.getById(data->at("user_to"));
//    // TODO: activeUsersProvider sa moze skor vola ActiveConnectionsProvider a tam by bol user a fd

    char buffer[4096];
    string message = "removed request"; // TODO: zmen spravu
    int receiveSendStatus;
    for (auto &userConnection: acceptorConnections) // access by reference to avoid copying
    {
        bzero(buffer, 4096);
        Helpers::sgets(buffer, 4096, &message);

        receiveSendStatus = send(userConnection->getSockfd(), buffer, 4096, 0);
    }

    return R"({"status": 200,"data":{}})";
}

