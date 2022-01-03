//
// Created by Jakub Rončák on 22/12/2021.
//

#include "JsonReader.h"

json JsonReader::read(const string &fileName, const json &filters, json &filtered) {

    ifstream myfile;
    json j;

    myfile.open(fileName);
    cout << myfile.is_open() << endl;
    if (myfile.is_open()) {
        try {
            myfile >> j;
        }
        catch (json::parse_error &ex) {
            std::cerr << "parse error at byte " << ex.byte << std::endl;
        }
        myfile.close();
    }

    copy_if(j.begin(), j.end(),
            back_inserter(filtered), [&filters](const json &item) {

                if (!filters.contains("or") && !filters.contains("and")) {

                    return filterAnd(filters, item);

                } else {

                    for (auto it = filters.begin(); it != filters.end(); it++) {

                        if (it.key() == "or") {
                            return filterOr(it.value(), item);
                        } else {
                            return filterAnd(it.value(), item);
                        }

                    }
                    return true;
                }

            });

    return filtered;
}


bool JsonReader::filterOr(const json &filters, const json &item) {
    cout << "or" << endl << filters << endl;
    for (auto it = filters.begin(); it != filters.end(); it++) {
        cout << "key: " << it.value().is_object() << " value: " << it.value() << endl;

        if (filters.is_object()) {
            if (it.key() == "or") {
                if (filterOr(it.value(), item)) {
                    return true;
                }
            } else if (it.key() == "and") {
                if (filterAnd(it.value(), item)) {
                    return true;
                }
            } else {
                // operacia
                if (!item.contains(it.key())) {
                    throw logic_error("Filtered key is not in json!");
                }
                if (item[it.key()] == it.value()) {
                    return true;
                }
            }
        } else {
            for (auto itInner = it->begin(); itInner != it->end(); itInner++) {
                cout << "inner OR: " << itInner.value().is_object() << " value: " << itInner.value() << endl;
                if (itInner.key() == "or") {
                    if (filterOr(itInner.value(), item)) {
                        return true;
                    }
                } else if (itInner.key() == "and") {
                    if (filterAnd(itInner.value(), item)) {
                        return true;
                    }
                } else {
                    // operacia
                    if (!item.contains(itInner.key())) {
                        throw logic_error("Filtered key is not in json!");
                    }
                    if (item[itInner.key()] == itInner.value()) {
                        return true;
                    }
                }
            }
        }

    }
    return false;
}

bool JsonReader::filterAnd(const json &filters, const json &item) {
    cout << "and" << endl << filters << endl;

    for (auto it = filters.begin(); it != filters.end(); it++) {
        cout << "value:" << it.value() << ", hh: " << it.value().is_object() << endl;

        if (filters.is_object()) {
            if (it.key() == "or") {
                if (!filterOr(it.value(), item)) {
                    return false;
                }
            } else if (it.key() == "and") {
                if (!filterAnd(it.value(), item)) {
                    return false;
                }
            } else {
//                for (auto itInner = it->begin(); itInner != it->end(); itInner++) {
                cout << "inner:" << it.key() << ", " << it.value() << endl;

                if (!item.contains(it.key())) {
                    throw logic_error("Filtered key is not in json!");
                }
                if (item[it.key()] != it.value()) {
                    return false;
                }
//                }
//            return true;
            }
        } else {
            for (auto itInner = it->begin(); itInner != it->end(); itInner++) {

                if (itInner.key() == "or") {
                    if (!filterOr(itInner.value(), item)) {
                        return false;
                    }
                } else if (itInner.key() == "and") {
                    if (!filterAnd(itInner.value(), item)) {
                        return false;
                    }
                } else {
//                for (auto itInner = it->begin(); itInner != it->end(); itInner++) {
                    cout << "inner:" << itInner.key() << ", " << itInner.value() << endl;

                    if (!item.contains(itInner.key())) {
                        throw logic_error("Filtered key is not in json!");
                    }
                    if (item[itInner.key()] != itInner.value()) {
                        return false;
                    }
                }
//            return true;
            }
        }

    }
    return true;
}

