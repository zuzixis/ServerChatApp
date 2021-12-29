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
