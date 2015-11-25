#include "Nodo.hpp"

extern unsigned long long int dataframes_creados;
extern unsigned long long int nodos_creados;

Nodo::Nodo(DataFrame* df, CriterioNodo criterio, int profundidad) {
    this->dataFrame = df;
    this->criterio = criterio;
    this->splits = new std::vector<Nodo*>();
    this->profundidad = profundidad;
    nodos_creados++;
}

DataFrame* Nodo::obtenerDataFrame() {
    return this->dataFrame;
}

void Nodo::borrarDataFrame() {
    delete this->dataFrame;
}

bool Nodo::esHoja() {
    return (this->splits->size() == 0);
}


void Nodo::establecerCategoria(TuplasCat* cat) {
    this->categoria_final = cat;
}

TuplasCat* Nodo::obtenerCategoria() {
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



DataFrame* Nodo::filtrarDFPD(std::string Cat, std::string atribHijos) {
    CriterioNodo criterio(Cat,"=",atribHijos);
    DataFrame* df = this->dataFrame->filtrar(criterio);
    return df;
}

DataFrame* Nodo::filtrarDFNum(std::string Cat,std::string atribHijos,
                                                    std::string condicion) {
    CriterioNodo criterio(Cat,condicion,atribHijos);
    DataFrame* df = this->dataFrame->filtrar(criterio);
    return df;
}

Nodo::~Nodo() {
    delete this->splits;
    delete this->categoria_final;
    nodos_creados--;
}
