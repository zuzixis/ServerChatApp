//
// Created by Jakub Rončák on 22/12/2021.
//

#include "JsonReader.h"

json JsonReader::read(const string &fileName, const map<string, string> &filters) {

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
                map<string, string>::const_iterator it;

                for (it = filters.begin(); it != filters.end(); it++) {
                    if (!item.contains(it->first)) {
                        throw logic_error("Filtered key is not in json!");
                    }
                    if (!it->second.empty() && std::all_of(it->second.begin(), it->second.end(), ::isdigit)) {
                        // ide o cislo, teda ho prekonvertujem
                        if (item[it->first] != stoi(it->second)) {
                            return false;
                        }
                    } else {
                        if (item[it->first] != it->second) {
                            return false;
                        }
                    }
                }
                return true;
            });

    return filtered;
}

