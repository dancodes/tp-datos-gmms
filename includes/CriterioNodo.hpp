#include <iostream>
#include <string>

class CriterioNodo {
public:
    CriterioNodo(std::string atributo, std::string comparador, std::string condicion) {
        this->atributo = atributo;
        this->comparador = comparador;
        this->condicion = condicion;
    }

    std::string getAtributo() {
        return this->atributo;
    }
    std::string getComparador() {
        return this->comparador;
    }
    std::string getCondicion() {
        return this->condicion;
    }
private:
    std::string atributo;
    std::string comparador;
    std::string condicion;
};
