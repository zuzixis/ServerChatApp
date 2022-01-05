//
// Created by Jakub Rončák on 22/12/2021.
//

#include "JsonReader.h"

json JsonReader::read(const string &fileName, const json &filters, json &filtered) {

    cout << filters << endl;

    ifstream myfile;
    json j;

    myfile.open(fileName);
//    cout << myfile.is_open() << endl;
    if (myfile.is_open()) {
//        try {
        myfile >> j;
//        }
//        catch (json::parse_error &ex) {
//
//            std::cerr << "parse error at byte " << ex.byte << std::endl;
//        }
        myfile.close();
    }

    cout << "Filters" << filters << endl;
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
    for (auto it = filters.begin(); it != filters.end(); it++) {

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
                cout << it.key() << endl;
                cout << item << endl;

                if (!item.contains(it.key())) {
                    throw logic_error("Filtered key is not in json!");
                }
                if (item[it.key()] == it.value()) {
                    return true;
                }
            }
        } else {
            for (auto itInner = it->begin(); itInner != it->end(); itInner++) {
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
                    string value = itInner.value();
                    string itemValue = item[itInner.key()];
                    string valueMaybeLike = value.substr(0, 5);
                    string valueMaybeWord;

                    if (value.length() > 5) {
                        valueMaybeWord = value.substr(5);
                    } else {
                        valueMaybeWord = "";
                    }

                    if ((value.length() > 5 && valueMaybeLike == "LIKE:" &&
                         (itemValue.find(valueMaybeWord) != string::npos)) ||
                        (item[itInner.key()] == itInner.value())) {
                        return true;

                    }
                }
            }
        }

    }
    return false;
}

bool JsonReader::filterAnd(const json &filters, const json &item) {

    for (auto it = filters.begin(); it != filters.end(); it++) {

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

                if (!item.contains(it.key())) {
                    throw logic_error("Filtered key is not in json!");
                }
                string value = it.value();
                string itemValue = item[it.key()];
                string valueMaybeLike = value.substr(0, 5);
                string valueMaybeWord;

                if (value.length() > 5) {
                    valueMaybeWord = value.substr(5);
                } else {
                    valueMaybeWord = "";
                }

                cout << (value.length() > 5 && valueMaybeLike == "LIKE:") << endl;
                if (value.length() > 5 && valueMaybeLike == "LIKE:") {
                    if (itemValue.find(valueMaybeWord) == string::npos) {
                        return false;
                    }
                } else if (item[it.key()] != it.value()) {
                    return false;
                }
//                if (value.length() > 5 && valueMaybeLike == "LIKE:" &&
//                    (itemValue.find(valueMaybeWord) == string::npos)) {
//
//                }
//                if ((value.length() > 5 && valueMaybeLike == "LIKE:" &&
//                     (itemValue.find(valueMaybeWord) == string::npos)) ||
//                    (item[it.key()] != it.value())) {
//                    cout << "value.length(): " << value.length() << endl;
//                    cout << "valueMaybeLike: " << valueMaybeLike << endl;
//                    cout << "valueMaybeWord: " << valueMaybeWord << endl;
//                    cout << "itemValue.find(valueMaybeWord): " << itemValue.find(valueMaybeWord) << endl;
//                    cout << "string::npos: " << string::npos << endl;
////                    cout << "itemValue.find(valueMaybeWord) == string::npos: " << (itemValue.find(valueMaybeWord) == string::npos) << endl;
//                    cout << "item: " << item << endl;
//                    return false;
//                }
//                if () {
//                    return false;
//                }
//                }
//            return true;
            }
        } else {
            for (auto itInner = it->begin(); itInner != it->end(); itInner++) {
                cout << it->dump() << endl << itInner->dump() << endl;
                if (itInner.key() == "or") {
                    if (!filterOr(itInner.value(), item)) {
                        return false;
                    }
                } else if (itInner.key() == "and") {
                    if (!filterAnd(itInner.value(), item)) {
                        return false;
                    }
                } else {

                    if (!item.contains(itInner.key())) {
                        throw logic_error("Filtered key is not in json!");
                    }
                    string value = itInner.value();
                    string itemValue = item[itInner.key()];
                    string valueMaybeLike = value.substr(0, 5);
                    string valueMaybeWord;

                    if (value.length() > 5) {
                        valueMaybeWord = value.substr(5);
                    } else {
                        valueMaybeWord = "";
                    }

                    if ((value.length() > 5 && valueMaybeLike == "LIKE:" &&
                         (itemValue.find(valueMaybeWord) == string::npos)) ||
                        (item[itInner.key()] != itInner.value())) {
                        return false;
                    }
                }
            }
        }

    }
    return true;
}

