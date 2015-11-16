#pragma once

#include <string>

template <class T>
class Atributo;

class Crimen {
public:
    Crimen(double x, double y, std::string pdDistrict);
    double obtenerX();
    double obtenerY();
    std::string* obtenerPd();
    ~Crimen();
private:
    Atributo<double>* x;
    Atributo<double>* y;
    Atributo<std::string*>* pd;
};
