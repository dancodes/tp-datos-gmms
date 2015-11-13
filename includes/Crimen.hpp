#pragma once

#include <string>

class Crimen {
public:
    Crimen(double x, double y, std::string pdDistrict);
    double obtenerX();
    double obtenerY();
    std::string* obtenerPd();
    ~Crimen();
private:
    double x;
    double y;
    std::string* pd;
};
