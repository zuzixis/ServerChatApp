#pragma once

#include <map>
#include <iostream>
#include "json.hpp"
#include "JsonReader.h"
#include "Helpers.h"
#include "providers/ActiveUsersProvider.h"

using namespace std;
using json = nlohmann::json;

class UserController {
public:
    UserController();
    ~UserController();



    string search(const json *data);
};

