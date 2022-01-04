#pragma once

#include <map>
#include <iostream>
#include "json.hpp"
#include "JsonReader.h"
#include "Helpers.h"
#include "providers/ActiveUsersProvider.h"

using namespace std;
using json = nlohmann::json;

class RequestsController {

public:
    RequestsController();

    ~RequestsController();

    string askForRequestsContact(const json *data);

    string getContactRequests(const json *data);

    string confirmationContactRequest(const json *data);

    string rejectContactRequest(const json *data);
};

