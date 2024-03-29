#pragma once

#include <iostream>
#include <string>
#include <sstream>

class CriterioNodo {
public:
    CriterioNodo() {
    }
    CriterioNodo(std::string atributo, std::string comparador, std::string condicion) {
        this->atributo = atributo;
        this->comparador = comparador;
        this->condicion = condicion;

        if(atributo == "x" || atributo == "y") {
            this->condicion_numerica = std::stod(condicion);
        }
    }

    std::string* obtenerAtributo() {
        return &this->atributo;
    }
    std::string* obtenerComparador() {
        return &this->comparador;
    }
    std::string* obtenerCondicion() {
        return &this->condicion;
    }
    double obtenerCondicionNumerica() {
        return this->condicion_numerica;
    }

    std::string descripcion() {
        std::stringstream ss;
        ss << this->obtenerAtributo() << " " << this->obtenerComparador() << " " << this->obtenerCondicion();
        return ss.str();
    }
private:
    std::string atributo;
    std::string comparador;
    std::string condicion;
    double condicion_numerica;
};
