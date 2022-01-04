//
// Created by Jakub Rončák on 26/12/2021.
//

#include "Helpers.h"

string Helpers::gen_random(const int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

char *Helpers::sgets(char *str, int num, string *input) {
    const char *next = input->c_str();
    int numread = 0;

    while (numread + 1 < num && *next) {
        int isnewline = (*next == '\n');
        *str++ = *next++;
        numread++;
        // newline terminates the line but is included
        if (isnewline)
            break;
    }

    if (numread == 0)
        return NULL;  // "eof"

    // must have hit the null terminator or end of line
    *str = '\0';  // null terminate this tring
    // set up input for next call
    *input = next;
    return str;
}

bool Helpers::isNumber(const string &str) {
    for (char const &c: str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

bool Helpers::broadcastToUser(const int userId,string msg) {
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    vector<User *> acceptorConnections = activeUsersProvider.getById(userId);
//    // TODO: activeUsersProvider sa moze skor vola ActiveConnectionsProvider a tam by bol user a fd

    char buffer[4096];
    int receiveSendStatus;
    for (auto &userConnection: acceptorConnections) // access by reference to avoid copying
    {
        bzero(buffer, 4096);
        Helpers::sgets(buffer, 4096, &msg);

        receiveSendStatus = send(userConnection->getSockfd(), buffer, 4096, 0);
    }
    // TODO: return value
    return true;
}
