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

//    map<string, string>::const_iterator filteredIt;

//    map<string, string>::const_iterator it;
//    for (auto jsonIt = j.begin(); jsonIt != j.end(); jsonIt++) {
//        if ()
//        for (auto jsonObjIt = jsonIt->begin(); jsonObjIt != jsonIt->end(); jsonObjIt++) {
//
//            for (it = filters.begin(); it != filters.end(); it++) {
//                if (!jsonIt->contains(it->first)) {
//                    throw logic_error("Filtered key is not in json!");
//                }
////                if (!it->second.empty() && all_of(it->second.begin(), it->second.end(), ::isdigit)) {
////                    // ide o cislo, teda ho prekonvertujem
////                    if (jsonIt->operator[]()[it->first] != stoi(it->second)) {
////                        return false;
////                    }
////                } else {
////                    if (item[it->first] != it->second) {
////                        return false;
////                    }
////                }
//            }
//        }
//    }
//    json filtered;
//    auto *filtered = new vector<map<string, string>>();
//
//    for (auto it = RecentFiles.begin(); it != RecentFiles.end(); ++it)/
//
//    for_each(auto jsonIt = j.begin(), jsonIt != j.end(), [&filtered,&filters] {
//        map<string, string>::const_iterator it;
//        for (it = filters.begin(); it != filters.end(); it++) {
//            if (!item.contains(it->first)) {
//                throw logic_error("Filtered key is not in json!");
//            }
//            if (!it->second.empty() && all_of(it->second.begin(), it->second.end(), ::isdigit)) {
//                // ide o cislo, teda ho prekonvertujem
//                if (item[it->first] != stoi(it->second)) {
//                    return false;
//                }
//            } else {
//                if (item[it->first] != it->second) {
//                    return false;
//                }
//            }
//        }
//    });

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

