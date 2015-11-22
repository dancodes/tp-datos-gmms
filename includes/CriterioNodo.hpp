#include <iostream>
#include <string>

class CriterioNodo {
public:
    CriterioNodo(std::string atributo, std::string comparador, std::string condicion) {
        this->atributo = atributo;
        this->comparador = comparador;
        this->condicion = condicion;
    }

    std::string atributo() {
        return this->atributo;
    }
    std::string comparador() {
        return this->comparador;
    }
    std::string condicion() {
        return this->condicion;
    }
private:
    std::string atributo;
    std::string comparador;
    std::string condicion;
};
