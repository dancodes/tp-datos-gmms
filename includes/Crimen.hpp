#pragma once

#include <string>
#include <map>

class NAtributo;
class NAtributoNumerico;
class NAtributoCategorico;

class Crimen {
public:
    Crimen(double x, double y, std::string pdDistrict, std::string category);
    Crimen(double x, double y, std::string pdDistrict);
    void* obtenerAtributo(std::string nombre_atributo);
    double obtenerX();
    double obtenerY();
    double obtenerNumerico(char); // x para devolver x e y para devolver y
    std::string* obtenerPd();
    std::string* obtenerCategory();
    ~Crimen();
private:
    std::map<std::string, NAtributo*> atributos;
};
