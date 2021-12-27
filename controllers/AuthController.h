#pragma once

#include <map>
#include "../JsonReader.h"
#include "../models/User.h"
#include "../providers/ActiveUsersProvider.h"
#include <iostream>

using namespace std;

class AuthController {

    ActiveUsersProvider *activeUsersProvider;
public:
    AuthController(ActiveUsersProvider *activeUsersProvider);

    ~AuthController();

    map<string, string> login(const map<string, string> *data,int* connFd);

    bool logout(const map<string, string> *data);

    bool deleteAccount(const map<string, string> *data);

    bool createAccount(const map<string, string> *data);


};
