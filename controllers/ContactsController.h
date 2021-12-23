#pragma once
#include <map>
#include <iostream>

using namespace std;

class ContactsController {

public:
    ContactsController();
    ~ContactsController();

    map<string, string> getContacts(const map<string, string>* data);


};

