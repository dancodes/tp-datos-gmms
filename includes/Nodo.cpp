#include "Nodo.hpp"


Nodo::Nodo()
{
    this->atributo = " ";
    this->categoria = " ";
    this->infoGain = 0.0;
}

Nodo::Nodo(DataFrame* df , contenedor contIg){
    this->dataFrame = df;
    this->cont = contIg;

}

void Nodo::AgregarNodo(Nodo* nodoAAgregar){
    this->splits->push_back(nodoAAgregar);
}

Nodo::~Nodo()
{
    //dtor
}
