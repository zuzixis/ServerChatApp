#pragma once

#include "json.hpp"
#include "models/Model.h"
#include <fstream>
#include <iostream>
#include<map>

//
// Created by Jakub Rončák on 22/12/2021.
//
using json = nlohmann::json;
using namespace std;

class JsonReader {
public:
    static json read(const string &fileName, const map<string, int> &filters) {

        ifstream myfile;
        json j;

        myfile.open(fileName);
        cout << myfile.is_open() << endl;
        if (myfile.is_open()) {
            myfile >> j;
        }

        myfile.close();

        json filtered;
        std::copy_if(j.begin(), j.end(),
                     std::back_inserter(filtered), [&filters](const json &item) {
                    map<string, int>::const_iterator it;

                    for (it = filters.begin(); it != filters.end(); it++) {
                        if (!item.contains(it->first)) {
                            throw logic_error("Filtered key is not in json!");
                        }
                        if (item[it->first] != it->second) {
                            return false;
                        }
                    }
                    return true;
                });
//        std::cout << filtered << std::endl;

        return filtered;
    }
};


//#endif //SERVER_CHATAPP_JSONREADER_H
