#pragma once


#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <map>


#include "Categoria.hpp"

class NAtributo;
class NAtributoNumerico;
class NAtributoCategorico;

class Crimen {
public:
    Crimen(double x, double y, std::string pdDistrict, std::string category);
    void* obtenerAtributo(std::string nombre_atributo);
    double obtenerX();
    double obtenerY();
    double obtenerNumerico(char); // x para devolver x e y para devolver y
    std::string* obtenerPd();
    char obtenerCategory();
    std::string resumen();
    ~Crimen();
private:
    std::map<std::string, NAtributo*> atributos;
};
