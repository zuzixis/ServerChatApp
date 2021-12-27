#pragma once

#include "json.hpp"
#include "models/Model.h"
#include <fstream>
#include <iostream>
#include <vector>
#include<map>

//
// Created by Jakub Rončák on 22/12/2021.
//
using json = nlohmann::json;
using namespace std;

class JsonReader {
public:
    static json read(const string &fileName, const map<string, string> &filters, json &filtered);
};


//#endif //SERVER_CHATAPP_JSONREADER_H
