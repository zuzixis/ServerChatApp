#pragma once

#include <map>
#include "JsonReader.h"
#include "models/User.h"
#include "providers/ActiveUsersProvider.h"
#include <iostream>
#include <string>

using namespace std;


class AuthController {

    ActiveUsersProvider *activeUsersProvider;
public:
    AuthController(ActiveUsersProvider *activeUsersProvider);

    ~AuthController();


    string login(const json *data, int *connFd);

    string logout(const json *data);

    string deleteAccount(const json *data);

    static string createAccount(json *data);
};




