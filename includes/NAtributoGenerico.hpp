#pragma once

#include <string>

template <class T>
class NAtributoGenerico: public NAtributo {
public:
    NAtributoGenerico(std::string nombre, T valor)
    : NAtributo(nombre) {
        this->valor = valor;
    }
    void* obtenerValor();
private:
    T valor;
};

template <class T>

void* NAtributoGenerico<T>::obtenerValor() {
    return (void*)&(this->valor);
}
