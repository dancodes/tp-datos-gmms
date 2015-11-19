#include "Nodo.hpp"

Nodo::Nodo()
{
    //ctor
}

void Nodo::AgregarNodo(Nodo* nodoAAgregar){
    this->splits->push_back(nodoAAgregar);
}

Nodo::~Nodo()
{
    //dtor
}
