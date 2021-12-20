#pragma once

#include "iostream"
#include "Model.h"

using namespace std;

class Group : Model {
private:
//    static Group *loadedModels;
    int id;
    string name, createdAt;

public:
    Group(int id, const string &name, const string &createdAt);

    //Getter, Setter
    int getId() const;

    void setId(int id);

    const string &getName() const;

    void setName(const string &name);

    const string &getCreatedAt() const;

    void setCreatedAt(const string &createdAt);

    //CRUD
    static Model* get();

    bool save();

    bool update();

    bool remove();

};
