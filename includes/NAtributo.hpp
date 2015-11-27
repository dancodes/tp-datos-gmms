#pragma once

#include <string>

class NAtributo {
public:
    NAtributo(std::string nombre) {
        this->nombre = nombre;
    };
    std::string obtenerNombre() {
        return this->nombre;
    };
    virtual void* obtenerValor() = 0;
    virtual bool esNumerico() = 0;
    virtual ~NAtributo() {
    }

private:
    std::string nombre;
};
