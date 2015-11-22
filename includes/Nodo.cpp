#include "Nodo.hpp"


Nodo::Nodo(DataFrame* df, InfoEntropia* contIg, std::string atrib) {
    this->atributo = atrib;
    this->dataFrame = df;
    this->info_ig = contIg;
    this->setDatos();
    this->splits = new std::vector<Nodo*>();
}

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

double Nodo::obtenerIntervalo() {
    return this->intervalo;
}

std::string Nodo::obtenerAtrib() {
    return this->atributo;
}

void Nodo::setDatos() {
    double iGX = this->info_ig->iGTot - this->info_ig->iGX;
    double iGY = this->info_ig->iGTot - this->info_ig->iGY;
    double iGDP = this->info_ig->iGTot - this->info_ig->iGDP;

    if ((iGDP>iGX) && (iGDP>iGY)) {
        this->atributo = "pdDistrict";
        this->infoGain = iGDP;
        this->intervalo = 0;
    } else if ((iGX>iGY) && (iGX > iGDP)) {
        this->atributo = "x";
        this->infoGain = iGX;
        this->intervalo = this->info_ig->intervaloX;
    } else if ((iGY>iGX) && (iGY > iGDP)) {
        this->atributo = "y";
        this->infoGain = iGY;
        this->intervalo = this->info_ig->intervaloY;
    } else {
        std::cout << iGX << " // " << iGY << " // "<< iGDP << " !! maldito puto " << std::endl;
        this->atributo = "cat";
        this->categoria = this->info_ig->mayorCrimen;
    }
}

void Nodo::agregarNodo(Nodo* nodoAAgregar) {
    this->splits->push_back(nodoAAgregar);
}

std::string Nodo::obtenerCat() {
    return this->categoria;
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

Nodo::~Nodo()
{
    //dtor
}
