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
    bool esNumerico();
private:
    T valor;
};

template <class T>
void* NAtributoGenerico<T>::obtenerValor() {
    return (void*)&(this->valor);
}

template <class T>
bool NAtributoGenerico<T>::esNumerico() {
    return false;
}
