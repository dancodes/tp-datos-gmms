#pragma once

#include <string>

template <class T>
class Atributo {
public:
    Atributo(std::string nombre, T valor);
    std::string obtenerNombre();
    T obtenerValor();
private:
    std::string nombre;
    T valor;
};

template <class T>
Atributo<T>::Atributo(std::string nombre, T valor) {
    this->nombre = nombre;
    this->valor = valor;
}

template <class T>
std::string Atributo<T>::obtenerNombre() {
    return this->nombre;
}

template <class T>
T Atributo<T>::obtenerValor() {
    return this->valor;
}
