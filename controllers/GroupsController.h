#pragma once
#include <map>
#include <iostream>

using namespace std;


class GroupsController {

public:
    GroupsController();
    ~GroupsController();

    map<string, string> getGroups(const map<string, string>* data);

};
