#pragma once
#include <map>
#include <iostream>
#include "json.hpp"
#include "JsonReader.h"
#include "providers/ActiveUsersProvider.h"

using namespace std;
using json = nlohmann::json;

class GroupsController {

public:
    GroupsController();
    ~GroupsController();

    string getGroups(const json* data);

};
