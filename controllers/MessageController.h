#pragma once
#include <map>
#include <iostream>

using namespace std;


class MessageController {

public:
    MessageController();
    ~MessageController();

    map<string, string> getConversation(const map<string, string>* data);
    bool sendMessage(const map<string, string>* data);
    bool sendFile(const map<string, string>* data);
    bool sendImage(const map<string, string>* data);
};



