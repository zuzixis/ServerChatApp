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

    string login(const json *data,int* connFd);

    string logout(const User* user);

    string deleteAccount(const map<string, string> *data);

    static string createAccount(map<string, string> *data);
};
