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
    int userId = ActiveUsersProvider::getInstance().getActualUserId();
    // {or:{x:1,y:2}}

    if (!data->contains("word")) {
        return R"({"status": 422,"data":{"errors":[{"word":"Hľadaný výraz je povinný"}]}})";
    }

    string x = data->at("word");
    string filtersString = R"({"name":"LIKE:)" + x + "\"}";

    json filters = json::parse(filtersString);

    json loadedUsers;
    JsonReader::read(Helpers::DATABASE_USERS, filters, loadedUsers);


    json ret;
    copy_if(
            loadedUsers.begin(), loadedUsers.end(),
            back_inserter(ret), [&userId](const json &item) {
                return (int) (item["id"]) != userId;
            });

    cout << ret << endl;
    return R"({"status": 200,"data":)" + (!ret.empty() ? ret.dump() : "[]") + "}";
}
