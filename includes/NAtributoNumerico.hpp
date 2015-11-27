#pragma once

#include <string>

class NAtributoNumerico: public NAtributo {
public:
    NAtributoNumerico(std::string nombre, double valor)
    : NAtributo(nombre) {
        this->valor = valor;
    }
    void* obtenerValor();
    bool esNumerico();
private:
    double valor;
};

bool NAtributoNumerico::esNumerico() {
    return false;
}

void* NAtributoNumerico::obtenerValor() {
    return (void*)&(this->valor);
}

//bool  NAtributo::esNumerico() {

//    return false;

//}
