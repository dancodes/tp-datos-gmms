#include "Nodo.hpp"

Nodo::Nodo()
{
    this->atributo = " ";
    this->categoria = " ";
    this->infoGain = 0.0;
}

Nodo::Nodo(DataFrame* df,std::string atrib,std::string cat,double IG){
    this->dataFrame = df;
    this->atributo = atrib;
    this->categoria = cat;
    this->infoGain = IG;
}

void Nodo::AgregarNodo(Nodo* nodoAAgregar){
    this->splits->push_back(nodoAAgregar);
}

Nodo::~Nodo()
{
    //dtor
}
