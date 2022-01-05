//
// Created by Jakub Rončák on 05/01/2022.
//

#include "UserController.h"

UserController::UserController() {

}

UserController::~UserController() {

}

string UserController::search(const json *data) {
    cout << *data << endl;
//    int userId = ActiveUsersProvider::getInstance().getActualUserId();
    // {or:{x:1,y:2}}

    if (!data->contains("word")) {
        return R"({"status": 422,"data":{}})";
    }

//    string filtersString = "{\"user_id\":" + to_string(userId);// +"}";
//    if (data->contains("word")) {
        string x = data->at("word");
    string filtersString = R"({"name":"LIKE:)" + x + "\"}";
//    }
//    filtersString += "}";

    json filters = json::parse(filtersString);

    json loadedUsers;
    JsonReader::read("../database/users.json", filters, loadedUsers);

    // {"or":[{"id":1},{"id":2}]}

//    string groupFiltersString = "{\"or\":[";
//    int x;
//    for (auto loadedGroupId: loadedGroupIds) {
//        x = loadedGroupId["group_id"];
//        groupFiltersString += ("{\"id\":" + to_string(x) + "},");
//    }
//    groupFiltersString = groupFiltersString.substr(0, groupFiltersString.size() - 1);
//    groupFiltersString += "]}";
//
//    json groupFilters = json::parse(groupFiltersString);
//
//    json loadedGroups;
//    JsonReader::read("database/groups.json", groupFilters, loadedGroups);
//    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
// TODO: ideme davat do usera spravy?

//    return user->getMessages();
    cout << loadedUsers << endl;
    return R"({"status": 200,"data":)" + (!loadedUsers.empty() ? loadedUsers.dump() : "[]") + "}";
}
