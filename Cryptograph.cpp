//
// Created by Jakub Rončák on 07/01/2022.
//

#include "Cryptograph.h"

string Cryptograph::decrypt(const string &in) {
    string out;
    for (char c: in) {
        int temp = (c - key);
        out += (char) temp;
    }

    return out;
}


string Cryptograph::encrypt(const string &in) {
    string out;


    for (char c: in) {
        int temp = (c + key);

        // Write temp as char in
        // output file
        out += (char) temp;
    }
    return out;
}
