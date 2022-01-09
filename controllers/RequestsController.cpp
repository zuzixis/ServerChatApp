#include "RequestsController.h"

string RequestsController::askForRequestsContact(const json *data) {

    cout << *data << endl;
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    int userFrom = activeUsersProvider.getActualUserId();
    if (!data->contains("user_to")) {
        return R"({"status": 422,"data":{"errors":[{"user_to":"Atribút je povinný"}]}})";
    }
    int userTo = data->at("user_to");

    if (!User::exists(userTo)) {
        return R"({"status": 400,"data":{"msg":"Uživateľ s takýmto id neexistuje."}})";
    }

    if (Contact::exists(userFrom, userTo)) {
        return R"({"status": 400,"data":{"msg":"Takéhoto uživateľa uz mate v kontaktoch."}})";
    }


    json filters = json::parse(
            "{\"or\":"s + "[{\"and\":{\"user_from\":" + to_string(userFrom) + ",\"user_to\":" + to_string(userTo) +
            "}},{\"and\":{\"user_to\":" +
            to_string(userFrom) + ",\"user_from\":" + to_string(userTo) + "}}]}");

    json loadedRequests;
    JsonReader::read(Helpers::DATABASE_CONTACT_REQUESTS, filters, loadedRequests);

    if (!loadedRequests.empty()) {
        return R"({"status": 400,"data":{"msg":"Požiadavka uŽ existuje"}})";
    }

    json newRequest;
    newRequest["user_from"] = userFrom;
    newRequest["user_to"] = userTo;

    JsonReader::read(Helpers::DATABASE_CONTACT_REQUESTS, {}, loadedRequests);
    loadedRequests.push_back(newRequest);

    ofstream file(Helpers::DATABASE_CONTACT_REQUESTS);
    file << loadedRequests;
    file.close();

    json users;
    string userFiltersString = "{\"id\":" + to_string(userFrom) + "}";
    JsonReader::read(Helpers::DATABASE_USERS, json::parse(userFiltersString), users);
    string userName = users[0]["name"];
    string broadJsonString =
            "{\"type\":" + to_string(3) + R"(,"data":{"message":"Prisla ziadost od uživateľa )" + userName
            + "\"}}";

    Helpers::broadcastToUser(userTo, broadJsonString);

    return R"({"status": 200,"data":{}})";

}

string RequestsController::getContactRequests(const json *data) {
    cout << *data << endl;
    int userId = ActiveUsersProvider::getInstance().getActualUserId();
    json filters = json::parse("{\"user_to\":" + to_string(userId) + "}");

    json loadedRequests;
    JsonReader::read(Helpers::DATABASE_CONTACT_REQUESTS, filters, loadedRequests);


    cout << loadedRequests << endl;

    json retUsers;
    if (!loadedRequests.empty()) {
        string usersFiltersString = "{\"or\":[";
        int x;
        for (auto loadedRequest: loadedRequests) {

            x = loadedRequest["user_from"];
            usersFiltersString += ("{\"id\":" + to_string(x) + "},");
        }
        usersFiltersString = usersFiltersString.substr(0, usersFiltersString.size() - 1);
        usersFiltersString += "]}";

        json userFilter = json::parse(usersFiltersString);
        JsonReader::read(Helpers::DATABASE_USERS, userFilter, retUsers);
    }

    cout << retUsers << endl;
    return R"({"status": 200,"data":)" + (!retUsers.empty() ? retUsers.dump() : "[]") + "}";
}

string RequestsController::confirmationContactRequest(const json *data) {
    cout << *data << endl;
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    int userTo = activeUsersProvider.getActualUserId();
    if (!data->contains("user_from")) {
        return R"({"status": 422,"data":{"errors":[{"user_from":"Atribút je povinný"}]}})";
    }
    int userFrom = data->at("user_from");

    if (!User::exists(userFrom)) {
        return R"({"status": 400,"data":{"msg":"Uživateľ s takýmto id neexistuje."}})";
    }

    json filters = json::parse(
            "{\"user_from\":" + to_string(userFrom) + ",\"user_to\":" + to_string(userTo) + "}");

    json loadedRequests;
    JsonReader::read(Helpers::DATABASE_CONTACT_REQUESTS, filters, loadedRequests);

    if (loadedRequests.empty()) {
        return R"({"status": 400,"data":{"msg":"Nikto s takýmto id vám neposlal požiadavku."}})";
    }

    json loadedContacts;
    JsonReader::read(Helpers::DATABASE_CONTACTS, {}, loadedContacts);

    loadedContacts.push_back(json::parse(
            "{\"user_1\":" + to_string(userFrom) + ", \"user_2\":" + to_string(userTo) + "}"));
    JsonReader::read(Helpers::DATABASE_CONTACT_REQUESTS, {}, loadedRequests);

    json newRequests;
    copy_if(
            loadedRequests.begin(), loadedRequests.end(),
            back_inserter(newRequests), [&userFrom, &userTo](const json &item) {
                if ((int) (item["user_from"]) != userFrom || (int) (item["user_to"]) != userTo) {
                    return true;
                }
                return false;
            });

    ofstream fileContacts(Helpers::DATABASE_CONTACTS);
    fileContacts << loadedContacts;
    fileContacts.close();

    ofstream fileRequests(Helpers::DATABASE_CONTACT_REQUESTS);
    fileRequests << newRequests;
    fileRequests.close();

    return R"({"status": 200,"data":{}})";
}

string RequestsController::rejectContactRequest(const json *data) {


    cout << *data << endl;
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    int userTo = activeUsersProvider.getActualUserId();
    if (!data->contains("user_from")) {
        return R"({"status": 422,"data":{"errors":[{"user_from":"Atribút je povinný"}]}})";
    }
    int userFrom = data->at("user_from");
    if (!User::exists(userFrom)) {
        return R"({"status": 400,"data":{"msg":"Uživateľ s takýmto id neexistuje."}})";
    }
    json filters = json::parse(
            "{\"user_from\":" + to_string(userFrom) + ",\"user_to\":" + to_string(userTo) + "}");

    json loadedRequests;
    JsonReader::read(Helpers::DATABASE_CONTACT_REQUESTS, filters, loadedRequests);


    if (loadedRequests.empty()) {
        return R"({"status": 400,"data":{"msg":""}})";
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

    ofstream fileRequests(Helpers::DATABASE_CONTACT_REQUESTS);
    fileRequests << newRequests;
    fileRequests.close();

    return R"({"status": 200,"data":{}})";


}

