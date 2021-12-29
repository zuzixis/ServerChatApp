#pragma once
#include <map>
#include <iostream>
#include "../providers/ActiveUsersProvider.h"
#include "../json.hpp"

using namespace std;
using json = nlohmann::json;

class MessageController {

public:
    MessageController();
    ~MessageController();

    string getConversation(const json* data);
    string sendMessage(const json* data);
    string sendFile(const json* data);
    string sendImage(const json* data);
};



