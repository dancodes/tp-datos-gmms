#include "Nodo.hpp"


Nodo::Nodo()
{
    this->atributo = " ";
    this->categoria = " ";
    this->infoGain = 0.0;
}

Nodo::Nodo(DataFrame* df, contenedor contIg, std::string atrib){
    this->atributo = atrib;
    this->dataFrame = df;
    this->cont = contIg;
    this->setDatos();
}

double Nodo::obtenerIntervalo(){
    return this->intervalo;
}

void Nodo::setDatos(){
    double iGX = this->cont.iGTot - this->cont.iGX;
    double iGY = this->cont.iGTot - this->cont.iGY;
    double iGDP = this->cont.iGTot - this->cont.iGDP;

    if ((iGDP>iGX) && (iGDP>iGY) && (cont.iGDP > 0)){
        this->categoria = "dp";
        this->infoGain = iGDP;
        this->intervalo = 0;
    }else if ((iGX>iGY) && (iGX > iGDP) && (iGX > 0)){
        this->categoria = "x";
        this->infoGain = iGX;
        this->intervalo = this->cont.intervaloX;
    }else if ((iGY>iGX) && (iGY > iGDP) && (iGY > 0)){
        this->categoria = "y";
        this->infoGain = iGY;
        this->intervalo = this->cont.intervaloY;
    }else {
        this->categoria = "cat";
        this->atributo = cont.mayorCrimen;

    }
}

void Nodo::agregarNodo(Nodo* nodoAAgregar){
    this->splits->push_back(nodoAAgregar);
}

std::string Nodo::obtenerCat(){
    return this->categoria;
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
