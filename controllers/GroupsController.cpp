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
        return R"({"status": 422,"data":{"errors":[{"word":"Hľadaný výraz je povinný"}]}})";
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
//    JsonReader::read(Helpers::DATABASE_GROUP, groupFilters, loadedGroups);
//    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
// TODO: ideme davat do usera spravy?

//    return user->getMessages();
    cout << loadedGroups << endl;
    return R"({"status": 200,"data":)" + (!loadedGroups.empty() ? loadedGroups.dump() : "[]") + "}";
}

string GroupsController::joinToGroup(const json *data) {
    cout << *data << endl;
    int userId = ActiveUsersProvider::getInstance().getActualUserId();

    if (!data->contains("group_id")) {
        return R"({"status": 422,"data":{"errors":[{"group_id":"Id skupiny je povinné"}]}})";
    }

    int groupId = data->at("group_id");

    if (!Group::exists(groupId)) {
        return R"({"status": 400,"data":{"errors":[{"group_id":"Skupina s daným id neexistuje"}]}})";
    }

    string filtersString = R"({"group_id":)" + to_string(groupId) + "}";

    json filters = json::parse(filtersString);

    json loadedItems;
    JsonReader::read(Helpers::DATABASE_GROUP_USERS, {}, loadedItems);
    cout << loadedItems << endl;
    json newData;
    newData["group_id"] = groupId;
    newData["user_id"] = userId;

    loadedItems.push_back(newData);
    ofstream file("database/group_users.json");
    file << loadedItems;
    file.close();

    return R"({"status": 200,"data":{}})";
}

string GroupsController::unjoinFromGroup(const json *data) {
    cout << *data << endl;
    int userId = ActiveUsersProvider::getInstance().getActualUserId();

    if (!data->contains("group_id")) {
        return R"({"status": 422,"data":{"errors":[{"group_id":"Id skupiny je povinné"}]}})";
    }

    int groupId = data->at("group_id");

    if (!Group::exists(groupId)) {
        return R"({"status": 400,"data":{"errors":[{"group_id":"Skupina s daným id neexistuje"}]}})";
    }

//    string filtersString = R"({"group_id":)" + to_string(groupId) + "}";

//    json filters = json::parse(filtersString);

    json actualJson,newJson;
    JsonReader::read(Helpers::DATABASE_GROUP_USERS, {}, actualJson);
    newJson.clear();
    copy_if(
            actualJson.begin(), actualJson.end(),
            back_inserter(newJson), [&groupId,&userId](const json &item) {
                return !((int) (item["group_id"]) == groupId && (int) (item["user_id"]) != userId);
//                return (int) (item["group_id"]) != groupId || (int) (item["group_id"]) != groupId;
            });

    ofstream fileGU("database/group_users.json");
    fileGU << (!newJson.empty() ? newJson : "[]");
    fileGU.close();

    return R"({"status": 200,"data":{}})";
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
            return R"({"status": 409,"data":{"msg":"Skupina s takýmto názvom uŽ existuje"}})";
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
    int loggedUserId = ActiveUsersProvider::getInstance().getActualUserId();
    json newData = json::parse(
            "{\"id\":" + to_string(newId) + R"(,"name":")" + data->at("name").get<string>() + R"(","created_at":")" +
            createdAt + "\",\"creator_id\":"+ to_string(loggedUserId)+"}");


    loadedItems.push_back(newData);
    ofstream file("database/groups.json");
    file << loadedItems;
    file.close();

    int userId = ActiveUsersProvider::getInstance().getActualUserId();

    string filtersString = R"({"group_id":)" + to_string(newId) + "}";
    json filters = json::parse(filtersString);

    loadedItems.clear();
    JsonReader::read(Helpers::DATABASE_GROUP_USERS, {}, loadedItems);
    cout << loadedItems << endl;
    newData.clear();
    newData["group_id"] = newId;
    newData["user_id"] = userId;

    loadedItems.push_back(newData);
    ofstream fileGU("database/group_users.json");
    fileGU << loadedItems;
    fileGU.close();
    return R"({"status": 200,"data":{}})";
}

string GroupsController::removeGroup(const json *data) {
    cout << *data << endl;
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    int myId = activeUsersProvider.getActualUserId();
    if (!data->contains("group_id")) {
        return R"({"status": 422,"data":{"errors":[{"group_id":"Atribút je povinný"}]}})";
    }
    int groupId = data->at("group_id");

    if (!Group::exists(groupId)) {
        return R"({"status": 400,"data":{"errors":[{"group_id":"Neexistuje takáto skupina."}]}})";
    }

    string filtData = "{\"id\":"+ to_string(groupId) +"}";
    json filters = json::parse(filtData);

    json actualJson;
    JsonReader::read(Helpers::DATABASE_GROUP, filters, actualJson);

    if (actualJson.empty() || actualJson.begin()->at("creator_id") != myId) {
        return R"({"status": 400,"data":{"msg":""}})";
    }

    actualJson.clear();
    JsonReader::read(Helpers::DATABASE_GROUP, {}, actualJson);

    if (actualJson.empty()) {
        return R"({"status": 400,"data":{"msg":""}})";
    }

    json newJson;
    copy_if(
            actualJson.begin(), actualJson.end(),
            back_inserter(newJson), [&groupId](const json &item) {
                int id = (int) (item["id"]);
                return id != groupId;
            });

    ofstream file("database/groups.json");
    file << (!newJson.empty() ? newJson : "[]");
    file.close();

    actualJson.clear();
    JsonReader::read(Helpers::DATABASE_GROUP_USERS, {}, actualJson);
    newJson.clear();
    copy_if(
            actualJson.begin(), actualJson.end(),
            back_inserter(newJson), [&groupId](const json &item) {
                return (int) (item["group_id"]) != groupId;
            });

    ofstream fileGU("database/group_users.json");
    fileGU << (!newJson.empty() ? newJson : "[]");
    fileGU.close();

    return R"({"status": 200,"data":{}})";
}
