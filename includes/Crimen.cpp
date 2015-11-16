#include "Crimen.hpp"
#include "Atributo.hpp"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;


Crimen::Crimen(double x, double y, std::string pdDistrict) {
    this->x = new Atributo<double>("x", x * 10e9);
    this->y = new Atributo<double>("y", y * 10e9);
    this->pd = new Atributo<std::string*>("pdDistrict", new std::string(pdDistrict));
}

double Crimen::obtenerX() {
    return this->x->obtenerValor();
}

double Crimen::obtenerY() {
    return this->y->obtenerValor();
}

string* Crimen::obtenerPd() {
    return this->pd->obtenerValor();
}

Crimen::~Crimen() {
    cout << "Deletin ..." << this->x->obtenerValor() << endl;
    delete this->x;
    delete this->y;
    delete this->pd;
    delete this->pd->obtenerValor();
}
