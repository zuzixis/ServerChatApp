//
// Created by Jakub Rončák on 22/12/2021.
//

#include "JsonReader.h"

json JsonReader::read(const string &fileName, const json &filters, json &filtered) {

    cout << filters << endl;

    ifstream myfile;
    json j;

    myfile.open(fileName);
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
    if (!filtered.empty() && filtered.begin()->contains("created_at")) {
        sort(filtered.begin(), filtered.end(), [](json a, json b) {
            return Helpers::string_to_time_t(a["created_at"]) < Helpers::string_to_time_t(b["created_at"]);
        });
    }

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
                    string value;
                    string itemValue;
                    string valueMaybeLike;
                    string valueMaybeWord;
                    if (itInner.value().is_string()) {
                        value = itInner.value().get<string>();
                        itemValue = item[itInner.key()];
                        valueMaybeLike = value.substr(0, 5);
                        if (value.length() > 5) {
                            valueMaybeWord = value.substr(5);
                        } else {
                            valueMaybeWord = "";
                        }

                    }
                    if (itInner.value().is_string() && value.length() > 5 && valueMaybeLike == "LIKE:") {
                        if (itemValue.find(valueMaybeWord) != string::npos) {
                            return true;
                        }
                    } else if (item[itInner.key()] == itInner.value()) {
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
                if (!item.contains(it.key())) {
                    throw logic_error("Filtered key is not in json!");
                }

                string value;
                string itemValue;
                string valueMaybeLike;
                string valueMaybeWord;
                if (it.value().is_string()) {
                    value = it.value().get<string>();
                    itemValue = item[it.key()];
                    valueMaybeLike = value.substr(0, 5);
                    if (value.length() > 5) {
                        valueMaybeWord = value.substr(5);
                    } else {
                        valueMaybeWord = "";
                    }

                }

                if (it.value().is_string() && value.length() > 5 && valueMaybeLike == "LIKE:") {
                    if (itemValue.find(valueMaybeWord) == string::npos) {
                        return false;
                    }
                } else if (item[it.key()] != it.value()) {
                    return false;
                }
            }
        } else {
            for (auto itInner = it->begin(); itInner != it->end(); itInner++) {
//                cout << it->dump() << endl << itInner->dump() << endl;
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
                    string value;
                    string itemValue;
                    string valueMaybeLike;
                    string valueMaybeWord;
                    if (itInner.value().is_string()) {
//                cout << "it.value()"<<it.value() << endl;
                        value = itInner.value().get<string>();
                        itemValue = item[itInner.key()];
                        valueMaybeLike = value.substr(0, 5);
                        if (value.length() > 5) {
                            valueMaybeWord = value.substr(5);
                        } else {
                            valueMaybeWord = "";
                        }

                    }


                    if (itInner.value().is_string() && (value.length() > 5 && valueMaybeLike == "LIKE:" &&
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

