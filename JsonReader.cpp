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

//    cout << "Filters" << filters << endl;
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
//    cout << "filtered" << filtered << endl;
    if (!filtered.empty() && filtered.begin()->contains("created_at")) {
        sort(filtered.begin(), filtered.end(), [](json a, json b) {
//            cout << a["created_at"] << "  " << b["created_at"] << endl;
//            cout << to_string(Helpers::string_to_time_t(
//                    a["created_at"])) << "  " << to_string(Helpers::string_to_time_t(b["created_at"])) << endl;
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
//                cout << it.key() << endl;
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
//                cout << "it.value()"<<itInner.value() << endl;
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
//                for (auto itInner = it->begin(); itInner != it->end(); itInner++) {
                cout << "item: " << item << endl;
                cout << "it.key(): " << it.key() << endl;
                if (!item.contains(it.key())) {
                    throw logic_error("Filtered key is not in json!");
                }

                string value;
                string itemValue;
                string valueMaybeLike;
                string valueMaybeWord;
                if (it.value().is_string()) {
//                cout << "it.value()"<<it.value() << endl;
                    value = it.value().get<string>();
                    itemValue = item[it.key()];
                    valueMaybeLike = value.substr(0, 5);
                    if (value.length() > 5) {
                        valueMaybeWord = value.substr(5);
                    } else {
                        valueMaybeWord = "";
                    }

                }



//                cout << (value.length() > 5 && valueMaybeLike == "LIKE:") << endl;
                if (it.value().is_string() && value.length() > 5 && valueMaybeLike == "LIKE:") {
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



//                cout << (value.length() > 5 && valueMaybeLike == "LIKE:") << endl;
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

