#pragma once
#include <map>
#include "../JsonReader.h"
#include "../models/User.h"
#include <iostream>

using namespace std;

class AuthController {

public:
    AuthController();
    ~AuthController();

    map<string, string> login(const map<string, string>* data);

    bool logout(const map<string, string>* data);

    bool deleteAccount(const map<string, string>* data);

    bool createAccount(const map<string, string>* data);



};
