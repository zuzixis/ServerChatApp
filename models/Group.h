#pragma once
#include "iostream"

using namespace std;

class Group {
private:
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
    bool save();

    bool update();

    bool remove();

};
