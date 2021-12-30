//
// Created by Jakub Rončák on 22/12/2021.
//

#include "JsonReader.h"

json JsonReader::read(const string &fileName, const map<string, string> &filters, json &filtered) {

    ifstream myfile;
    json j;

    myfile.open(fileName);
    cout << myfile.is_open() << endl;
    if (myfile.is_open()) {
        try
        {
            myfile >> j;
        }
        catch (json::parse_error& ex)
        {
            std::cerr << "parse error at byte " << ex.byte << std::endl;
        }
        myfile.close();
    }


    copy_if(j.begin(), j.end(),
            back_inserter(filtered), [&filters](const json &item) {
                map<string, string>::const_iterator it;

                for (it = filters.begin(); it != filters.end(); it++) {
                    if (!item.contains(it->first)) {
                        throw logic_error("Filtered key is not in json!");
                    }
                    if (!it->second.empty() && all_of(it->second.begin(), it->second.end(), ::isdigit)) {
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

