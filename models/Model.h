#pragma once

#include "iostream"
//
// Created by Jakub Rončák on 20/12/2021.
//
using namespace std;

class Model {
protected:
    FILE* file = nullptr;
public:
    Model(const string *file);
    ~Model();
// CRUD
    //TODO: implementovat v kazdej dcerskej triede metodu get, ktora bude obsahovat pracu so suborom,
    // prip. bude citat dany atribut a podla niecoho bude z nich filtrovat a vrati iba spravne objekty
    // premenene do modelov. Asi treba poslat do konstruktora modelu iba objekt ako text alebo pole
    // hodnot a uz v nom si tento text premenit na jednotlive atributy
    static Model* get();
// TODO: save uklada aktualny model do suboru, asi
    bool save();

    // TODO: asi to iste, ako save .. hmm.
    bool update();

    //TODO: vymaze dany model zo suboru. 
    bool remove();

protected:

};


