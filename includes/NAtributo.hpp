#pragma once

#include <string>

class NAtributo {
public:
    NAtributo(std::string nombre);
    std::string obtenerNombre();
    virtual void* obtenerValor() = 0;
    virtual ~NAtributo() {

    }
private:
    std::string nombre;
};

NAtributo::NAtributo(std::string nombre) {
    this->nombre = nombre;
}

std::string NAtributo::obtenerNombre() {
    return this->nombre;
}
