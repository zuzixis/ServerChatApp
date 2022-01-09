#pragma once
#include <map>
#include <iostream>
#include "json.hpp"
#include "JsonReader.h"
#include "providers/ActiveUsersProvider.h"

using namespace std;
using json = nlohmann::json;


class ContactsController {

public:
    string getContacts(const json* data);
    string removeFromContacts(const json* data);





};

