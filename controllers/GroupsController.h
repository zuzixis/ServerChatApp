#pragma once
#include <map>
#include <iostream>
#include "json.hpp"
#include "Helpers.h"
#include "models/Group.h"
#include "JsonReader.h"
#include "providers/ActiveUsersProvider.h"


using namespace std;
using json = nlohmann::json;

class GroupsController {


public:
    GroupsController();
    ~GroupsController();

    string getGroups(const json* data);
    string search(const json* data);
    string create(const json* data);
    string joinToGroup(const json* data);
    string unjoinFromGroup(const json* data);

    string removeGroup(const json *json);
};
