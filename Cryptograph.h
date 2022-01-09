#pragma once
#include <iostream>

using namespace std;
class Cryptograph {
    static const char key = 'x';
public:
    static string decrypt(const string& input);
    static string encrypt(const string& input);
};

