#pragma once

#include <string>

class NAtributoCategorico: public NAtributo {
public:
    NAtributoCategorico(std::string nombre, std::string* valor)
    : NAtributo(nombre) {
        this->valor = valor;
    }
    void* obtenerValor();
    bool esNumerico();
    ~NAtributoCategorico();
private:
    std::string* valor;
};

void* NAtributoCategorico::obtenerValor() {
    return (void*)(this->valor);
}

bool NAtributoCategorico::esNumerico() {
    return false;
}

NAtributoCategorico::~NAtributoCategorico() {

    delete this->valor;
}
