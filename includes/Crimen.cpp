#include "Crimen.hpp"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

Crimen::Crimen(double x, double y, std::string pdDistrict) {
    this->x = x * 10e9;
    this->y = y * 10e9;
    this->pd = new std::string(pdDistrict);
}

double Crimen::obtenerX() {
    return this->x;
}

double Crimen::obtenerY() {
    return this->y;
}

string* Crimen::obtenerPd() {
    return this->pd;
}

Crimen::~Crimen() {
    delete this->pd;
}
