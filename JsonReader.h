#pragma once

#include "json.hpp"
#include "models/Model.h"
#include <fstream>
#include <iostream>
//
// Created by Jakub Rončák on 22/12/2021.
//
using json = nlohmann::json;
using namespace std;

class JsonReader {
public:
    static json read(const string &fileName, const int id) {

        ifstream myfile;
        json j;

        myfile.open(fileName);
        cout << myfile.is_open() << endl;
        if (myfile.is_open()) {
            myfile >> j;
        }

        json filtered;
        std::copy_if(j.begin(), j.end(),
                     std::back_inserter(filtered), [](const json& item) {
                    return item.contains("id") && item["id"] == 2;
                });
        std::cout << filtered << std::endl;

        return j;
    }
};


//#endif //SERVER_CHATAPP_JSONREADER_H
