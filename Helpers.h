#pragma once
#include "iostream"
#include "models/User.h"
#include "providers/ActiveUsersProvider.h"
#include <cstdio>
#include <ctime>

using namespace std;
class Helpers {
public:
    static string gen_random(const int len);
    static char *sgets(char *str, int num, string *input);
    static bool isNumber(const string &str);
    static bool broadcastToUser(const int userId,string msg);
    static string currentDateTime();
    static time_t string_to_time_t(string s);
};
