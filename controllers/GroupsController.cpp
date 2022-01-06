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

    string filtersString = "{\"user_id\":" + to_string(userId) + "}";

    json filters = json::parse(filtersString);

    json loadedGroups;
    json loadedGroupIds;
    JsonReader::read(Helpers::DATABASE_GROUP_USERS, filters, loadedGroupIds);

    // {"or":[{"id":1},{"id":2}]}
    if (!loadedGroupIds.empty()) {

        string groupFiltersString = "{\"or\":[";
        int x;
        for (auto loadedGroupId: loadedGroupIds) {
            x = loadedGroupId["group_id"];
            groupFiltersString += ("{\"id\":" + to_string(x) + "},");
        }
        groupFiltersString = groupFiltersString.substr(0, groupFiltersString.size() - 1);
        groupFiltersString += "]}";

        json groupFilters = json::parse(groupFiltersString);

        JsonReader::read(Helpers::DATABASE_GROUP, groupFilters, loadedGroups);
        cout << loadedGroups << endl;
    }
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
    JsonReader::read(Helpers::DATABASE_GROUP, filters, loadedGroups);

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
//    JsonReader::read("../database/groups.json", groupFilters, loadedGroups);
//    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
// TODO: ideme davat do usera spravy?

//    return user->getMessages();
    cout << loadedGroups << endl;
    return R"({"status": 200,"data":)" + (!loadedGroups.empty() ? loadedGroups.dump() : "[]") + "}";
}

string GroupsController::create(const json *data) {
    json loadedItems;
    JsonReader::read(Helpers::DATABASE_GROUP, {}, loadedItems);
    //JsonReader::read("skuska.json", {}, loadedUsers);

    if (!data->contains("name")) {
        return R"({"status": 422,"data":{"errors":[{"name":"Názov je povinný"}]}})";
    }

    for (auto group: loadedItems) {
        if (group["name"] == data->at("name")) {
            return R"({"status": 409,"data":{}})";
        }
    }
    int newId;
    if (loadedItems.empty()) {
        newId = 1;
    } else {
        cout << loadedItems.back().at("id") << endl;
        newId = (int) loadedItems.back().at("id") + 1;
    }

    string createdAt = Helpers::currentDateTime();
    json newData = json::parse(
            "{\"id\":" + to_string(newId) + R"(,"name":")" + data->at("name").get<string>() + R"(","created_at":")" +
            createdAt + "\"}");


    loadedItems.push_back(newData);
    ofstream file(Helpers::DATABASE_GROUP);
    file << loadedItems;
    file.close();
    return R"({"status": 200,"data":{}})";
}
