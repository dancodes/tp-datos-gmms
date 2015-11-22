#include "Nodo.hpp"
#include "InfoEntropia.hpp"


Nodo::Nodo()
{
    this->atributo = " ";
    this->categoria = " ";
    this->infoGain = 0.0;

    this->splits = new std::vector<Nodo*>();
}

Nodo::Nodo(DataFrame* df, InfoEntropia* contIg, std::string atrib){
    this->atributo = atrib;
    this->dataFrame = df;
    this->info_ig = contIg;
    this->setDatos();
    this->splits = new std::vector<Nodo*>();
}

double Nodo::obtenerIntervalo(){
    return this->intervalo;
}

void Nodo::setDatos(){
    double iGX = this->info_ig->iGTot - this->info_ig->iGX;
    double iGY = this->info_ig->iGTot - this->info_ig->iGY;
    double iGDP = this->info_ig->iGTot - this->info_ig->iGDP;

    if ((iGDP>iGX) && (iGDP>iGY)){
        this->categoria = "pdDistrict";
        this->infoGain = iGDP;
        this->intervalo = 0;
    } else if ((iGX>iGY) && (iGX > iGDP)){
        this->categoria = "x";
        this->infoGain = iGX;
        this->intervalo = this->info_ig->intervaloX;
    } else if ((iGY>iGX) && (iGY > iGDP)){
        this->categoria = "y";
        this->infoGain = iGY;
        this->intervalo = this->info_ig->intervaloY;
    } else {
        this->categoria = "cat";
        this->atributo = this->info_ig->mayorCrimen;
    }
}

void Nodo::agregarNodo(Nodo* nodoAAgregar){
    this->splits->push_back(nodoAAgregar);
}

std::string Nodo::obtenerCat(){
    return this->categoria;
}


std::vector<Nodo*>* Nodo::obtenerHijos() {
    return this->splits;
}

std::vector<std::string>* Nodo::obtenerListaAtrib(){
    std::map<std::string,unsigned int> diccAtrib = std::map<std::string,unsigned int>();
    std::vector<std::string>* listaAtributos = new std::vector<std::string>();
    for(int i = 0; i < this->dataFrame->cantidad(); i++) {
        Crimen* actual = dataFrame->at(i);
        std::string atributo_actual = *actual->obtenerPd();
        if(diccAtrib.count(atributo_actual)==0){
            diccAtrib[atributo_actual]=1;
            listaAtributos->push_back(atributo_actual);
        }
    }
    return listaAtributos;
}

DataFrame* Nodo::filtrarDFPD(std::string Cat,std::string atribHijos){
    DataFrame* df = this->dataFrame->filtrar(Cat,"=",atribHijos);
    return df;
}

DataFrame* Nodo::filtrarDFNum(std::string Cat,std::string atribHijos,
                                                    std::string condicion){
    DataFrame* df = this->dataFrame->filtrar(Cat,condicion,atribHijos);
    return df;
}

Nodo::~Nodo()
{
    //dtor
}
