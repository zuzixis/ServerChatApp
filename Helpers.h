//
// Created by Jakub Rončák on 26/12/2021.
//

#pragma once
#include "iostream"

using namespace std;
class Helpers {
public:
    static string gen_random(const int len);
    static char *sgets(char *str, int num, string *input);
    static bool isNumber(const string &str);
};
