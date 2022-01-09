#pragma once

#include "json.hpp"
#include "models/Model.h"
#include "Helpers.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>


//
// Created by Jakub Rončák on 22/12/2021.
//


using json = nlohmann::json;
using namespace std;

class JsonReader {
public:
    static json read(const string &fileName, const json &filters, json &filtered);

private:
    static bool filterOr(const json &filters, const json &item);

    static bool filterAnd(const json &filters, const json &item);
};
