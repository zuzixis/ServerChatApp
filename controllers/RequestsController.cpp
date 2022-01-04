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

    if (!User::exists(userTo) || Contact::exists(userFrom, userTo)) {
        return R"({"status": 400,"data":{}})";
    }
    json filters = json::parse(
            "{\"or\":"s + "[{\"and\":{\"user_from\":" + to_string(userFrom) + ",\"user_to\":" + to_string(userTo) +
            "}},{\"and\":{\"user_to\":" +
            to_string(userFrom) + ",\"user_from\":" + to_string(userTo) + "}}]}");

    json loadedRequests;
    JsonReader::read("database/contact_requests.json", filters, loadedRequests);

    if (!loadedRequests.empty()) {
        return R"({"status": 400,"data":{}})";
    }

    json newRequest;
    newRequest["user_from"] = userFrom;
    newRequest["user_to"] = userTo;
//    newRequest["status"] = "waiting";

    JsonReader::read("database/contact_requests.json", {}, loadedRequests);
    loadedRequests.push_back(newRequest);

    ofstream file("database/contact_requests.json");
    file << loadedRequests;
    file.close();

    Helpers::broadcastToUser(userTo, data->dump());

    return R"({"status": 200,"data":{}})";

}

string RequestsController::getContactRequests(const json *data) {
    cout << *data << endl;
    int userId = ActiveUsersProvider::getInstance().getActualUserId();
    // {"and":{or:{x:1,y:2},status:waiting}}
    json filters = json::parse(
            R"({"or":)"s + "{\"user_from\":" + to_string(userId) + ",\"user_to\":" + to_string(userId) + "}}");

    json loadedRequests;
    JsonReader::read("database/contact_requests.json", filters, loadedRequests);

    cout << loadedRequests << endl;
    return R"({"status": 200,"data":)" + (!loadedRequests.empty() ? loadedRequests.dump() : "[]") + "}";
}

string RequestsController::confirmationContactRequest(const json *data) {
    cout << *data << endl;
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    int userTo = activeUsersProvider.getActualUserId();
    int userFrom = data->at("user_from");


    json filters = json::parse(
            "{\"user_from\":" + to_string(userFrom) + ",\"user_to\":" + to_string(userTo) + "}");

    json loadedRequests;
    JsonReader::read("database/contact_requests.json", filters, loadedRequests);

    if (loadedRequests.empty()) {
        return R"({"status": 400,"data":{}})";
    }

    json loadedContacts;
//    json editedRequest = loadedContacts[0];
//    editedRequest["status"] = "confirmed";

    JsonReader::read("database/contacts.json", {}, loadedContacts);
    loadedContacts.push_back(
            "{\"user_1\":" + to_string(userFrom) + ", \"user_2\":" + to_string(userTo) + "}");
    JsonReader::read("database/contact_requests.json", {}, loadedRequests);

    json newRequests;
    copy_if(
            loadedRequests.begin(), loadedRequests.end(),
            back_inserter(newRequests), [&userFrom, &userTo](const json &item) {
                if ((int) (item["user_from"]) != userFrom || (int) (item["user_to"]) != userTo) {
                    return true;
                }
                return false;
            });

    ofstream fileContacts("database/contacts.json");
    fileContacts << loadedContacts;
    fileContacts.close();

    ofstream fileRequests("database/contact_requests.json");
    fileRequests << newRequests;
    fileRequests.close();

    Helpers::broadcastToUser(userFrom, "Potvrdena ziadost s " + to_string(userTo));

    return R"({"status": 200,"data":{}})";
}

string RequestsController::rejectContactRequest(const json *data) {

    cout << *data << endl;
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    int userTo = activeUsersProvider.getActualUserId();
    int userFrom = data->at("user_from");

    json filters = json::parse(
            "{\"user_from\":" + to_string(userFrom) + ",\"user_to\":" + to_string(userTo) + "}");

    json loadedRequests;
    JsonReader::read("database/contact_requests.json", filters, loadedRequests);


    if (loadedRequests.empty()) {
        return R"({"status": 400,"data":{}})";
    }

    json newRequests;
    copy_if(
            loadedRequests.begin(), loadedRequests.end(),
            back_inserter(newRequests), [&userFrom, &userTo](const json &item) {
                if ((int) (item["user_from"]) != userFrom || (int) (item["user_to"]) != userTo) {
                    return true;
                }
                return false;
            });

    ofstream fileRequests("database/contact_requests.json");
    fileRequests << newRequests;
    fileRequests.close();

    Helpers::broadcastToUser(userFrom, "Zamietnuta ziadost s " + to_string(userTo));

    return R"({"status": 200,"data":{}})";
}

