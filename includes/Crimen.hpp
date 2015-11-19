#pragma once

#include <string>

template <class T>
class Atributo;

class Crimen {
public:
    Crimen(double x, double y, std::string pdDistrict, std::string category);
    Crimen(double x, double y, std::string pdDistrict);
    double obtenerX();
    double obtenerY();
    double obtenerNumerico(char); // x para devolver x e y para devolver y
    std::string* obtenerPd();
    std::string* obtenerCategory();
    ~Crimen();
private:
    Atributo<double>* x;
    Atributo<double>* y;
    Atributo<std::string*>* pd;
    Atributo<std::string*>* ct;
};
