#pragma once
#include <map>
#include <iostream>
#include "providers/ActiveUsersProvider.h"
#include "json.hpp"

#pragma comment(lib, "Ws2_32.lib")
#define bzero(s, n) memset((s), 0, (n))
#define bcopy(s1, s2, n) memmove((s2), (s1), (n))
#include <mutex>

using namespace std;
using json = nlohmann::json;

class MessageController {

public:
    MessageController();
    ~MessageController();


    json getConversation(const json *data);
    json getMessageById(const json *data);
    string sendMessage( json* data);

//    string sendFile(const json* data);
//    string sendImage(const json* data);
};



