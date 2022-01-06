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


    //POUŽITIE ZUZKA
    static constexpr const char* DATABASE_USERS = "../database/users.json";
    static constexpr const char* DATABASE_CONTACTS = "../database/contacts.json";
    static constexpr const char* DATABASE_MESSAGES = "../database/messages.json";
    static constexpr const char* DATABASE_CONTACT_REQUESTS = "../database/contact_requests.json";
    static constexpr const char* DATABASE_GROUP_USERS = "../database/group_users.json";
    static constexpr const char* DATABASE_GROUP = "../database/groups.json";
    static constexpr const char* IP ="158.193.128.160";



    //POUŽITIE KUBO
    /*static constexpr const char* DATABASE_USERS = "database/users.json";
    static constexpr const char* DATABASE_CONTACTS = "database/contacts.json";
    static constexpr const char* DATABASE_MESSAGES = "database/messages.json";
    static constexpr const char* DATABASE_CONTACT_REQUESTS = "database/contact_requests.json";
    static constexpr const char* DATABASE_GROUP_USERS = "database/group_users.json";
    static constexpr const char* DATABASE_GROUP = "database/groups.json";
    static constexpr const char* IP ="127.0.0.1";*/
};
