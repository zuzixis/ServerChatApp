#pragma once
#include <map>
#include <iostream>

using namespace std;


class RequestsController {

public:
    RequestsController();
    ~RequestsController();

    bool askForRequestsContact(const map<string, string>* data);
    map<string, string> getContactRequests(const map<string, string>* data);
    bool confirmationContactRequest(const map<string, string>* data){

    };
};

