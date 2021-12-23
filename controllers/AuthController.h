#pragma once
#include <map>
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
