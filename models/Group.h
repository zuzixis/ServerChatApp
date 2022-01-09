#pragma once
#include <iostream>
#include "Model.h"
#include "json.hpp"
#include "JsonReader.h"


using namespace std;

class Group : public Model{
private:
    int id;
    string name, createdAt;


public:
    Group() : Model(){
        id = 0;
        name = "";
        createdAt = "";
    }


    Group(const string *file,int id, const string &name, const string &createdAt) : Model(file){
        this->id = id;
        this->name = name;
        this->createdAt = createdAt;
    };

    ~Group(){
        //TODO:Treba implementovať, dealokovať pamat co sa vytvorilo cez new
    }

    //Gettery, Settery
    int getId() const;
    void setId(int id);
    const string &getName() const;
    void setName(const string &name);
    const string &getCreatedAt() const;
    void setCreatedAt(const string &createdAt);

    //Implemenrtácia zdedených metód
    Model *get() override;
    bool save() override;
    bool update() override;
    bool remove(int id) override;
    static bool exists(const int id);
    static json getMembers(const int id);
};