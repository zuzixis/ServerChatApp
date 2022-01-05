//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "GroupsController.h"

GroupsController::GroupsController() {

}

GroupsController::~GroupsController() {

}

string GroupsController::getGroups(const json *data) {
    cout << *data << endl;
    int userId = ActiveUsersProvider::getInstance().getActualUserId();

    string filtersString = "{\"user_id\":" + to_string(userId) +"}";

    json filters = json::parse(filtersString);

    json loadedGroupIds;
    JsonReader::read("database/group_users.json", filters, loadedGroupIds);

    // {"or":[{"id":1},{"id":2}]}

    string groupFiltersString = "{\"or\":[";
    int x;
    for (auto loadedGroupId: loadedGroupIds) {
        x = loadedGroupId["group_id"];
        groupFiltersString += ("{\"id\":" + to_string(x) + "},");
    }
    groupFiltersString = groupFiltersString.substr(0, groupFiltersString.size() - 1);
    groupFiltersString += "]}";

    json groupFilters = json::parse(groupFiltersString);

    json loadedGroups;
    JsonReader::read("database/groups.json", groupFilters, loadedGroups);
//    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
// TODO: ideme davat do usera spravy?

//    return user->getMessages();
    cout << loadedGroups << endl;
    return R"({"status": 200,"data":)" + (!loadedGroups.empty() ? loadedGroups.dump() : "[]") + "}";
}

string GroupsController::search(const json *data) {
    cout << *data << endl;
//    int userId = ActiveUsersProvider::getInstance().getActualUserId();

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

    json loadedGroups;
    JsonReader::read("database/groups.json", filters, loadedGroups);

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
    cout << loadedGroups << endl;
    return R"({"status": 200,"data":)" + (!loadedGroups.empty() ? loadedGroups.dump() : "[]") + "}";
}
