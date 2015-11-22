#include "Crimen.hpp"

#include "NAtributo.hpp"
#include "NAtributoNumerico.hpp"
#include "NAtributoCategorico.hpp"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;


Crimen::Crimen(double x, double y, std::string pdDistrict,  std::string category) {
    this->atributos["x"] = new NAtributoNumerico("x", x * 10e9);
    this->atributos["y"] = new NAtributoNumerico("y", y * 10e9);
    this->atributos["pd"] = new NAtributoCategorico("pdDistrict", new std::string(pdDistrict));
    this->atributos["ct"] = new NAtributoCategorico("category", new std::string(category));
}
Crimen::Crimen(double x, double y, std::string pdDistrict) {

    this->atributos["x"] = new NAtributoNumerico("x", x * 10e9);
    this->atributos["y"] = new NAtributoNumerico("y", y * 10e9);
    this->atributos["pd"] = new NAtributoCategorico("pdDistrict", new std::string(pdDistrict));
    this->atributos["ct"] = new NAtributoCategorico("category", new std::string("No Category"));
}

void* Crimen::obtenerAtributo(std::string nombre_atributo) {
    return this->atributos[nombre_atributo]->obtenerValor();
}

double Crimen::obtenerX() {
    return *(double*)(this->atributos["x"]->obtenerValor());
}

double Crimen::obtenerY() {
    return *(double*)(this->atributos["y"]->obtenerValor());
}

string* Crimen::obtenerPd() {
    return (std::string*)(this->atributos["pd"]->obtenerValor());
}

string* Crimen::obtenerCategory() {
    return (std::string*)(this->atributos["ct"]->obtenerValor());
}

double Crimen::obtenerNumerico(char c) {
    double ret;
    if (c == 'x') {
        ret = obtenerX();
    }else {
        ret = obtenerY();
    }
    return ret;
}

Crimen::~Crimen() {
    /*cout << "Deletin ..." << this->x->obtenerValor() << endl;
    delete this->x;
    delete this->y;
    delete this->pd;*/
    //delete this->pd->obtenerValor();
}
