#include "Nodo.hpp"

Nodo::Nodo(DataFrame* df, CriterioNodo criterio, int profundidad) {
    this->dataFrame = df;
    this->criterio = criterio;
    this->splits = new std::vector<Nodo*>();
    this->profundidad = profundidad;
}

DataFrame* Nodo::obtenerDataFrame() {
    return this->dataFrame;
}

bool Nodo::esHoja() {
    return (this->splits->size() == 0);
}


void Nodo::establecerCategoria(std::string cat) {
    this->categoria_final = cat;
}

std::string Nodo::obtenerCategoria() {
    return this->categoria_final;
}

int Nodo::obtenerProfundidad() {
    return this->profundidad;
}

CriterioNodo Nodo::obtenerCriterio() {
    return this->criterio;
}

void Nodo::agregarNodo(Nodo* nodoAAgregar) {
    this->splits->push_back(nodoAAgregar);
}


std::vector<Nodo*>* Nodo::obtenerHijos() {
    return this->splits;
}



DataFrame* Nodo::filtrarDFPD(std::string Cat,std::string atribHijos) {
    DataFrame* df = this->dataFrame->filtrar(Cat,"=",atribHijos);
    return df;
}

DataFrame* Nodo::filtrarDFNum(std::string Cat,std::string atribHijos,
                                                    std::string condicion) {
    DataFrame* df = this->dataFrame->filtrar(Cat,condicion,atribHijos);
    return df;
}

Nodo::~Nodo() {
    delete this->splits;
    delete this->info_ig;
}
