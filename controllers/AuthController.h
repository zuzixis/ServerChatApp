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

    bool logout(const User* user);

    bool deleteAccount(const map<string, string> *data);

    static bool createAccount(map<string, string> *data);


};
