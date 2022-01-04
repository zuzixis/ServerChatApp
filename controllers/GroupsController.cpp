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
//    int userTo = data->at("user_to");
    // {or:{x:1,y:2}}
    json filters = json::parse("{\"user_id\":" + to_string(userId) + "}");

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
