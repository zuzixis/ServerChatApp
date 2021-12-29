#pragma once
#include <map>
#include <iostream>
#include "../JsonReader.h"

using namespace std;

class MessageController {

public:
    MessageController();
    ~MessageController();

    string getConversation(const json *data);
    string sendMessage(const json *data);
    string sendFile(const json *data);
    string sendImage(const json *data);
};



