#include "Crimen.hpp"


#include "NAtributo.hpp"
#include "NAtributoNumerico.hpp"
#include "NAtributoCategorico.hpp"
#include "NAtributoGenerico.hpp"

using namespace std;


Crimen::Crimen(double x, double y, std::string pdDistrict,  std::string category) {
    this->atributos["x"] = new NAtributoNumerico("x", x * 10e9);
    this->atributos["y"] = new NAtributoNumerico("y", y * 10e9);
    this->atributos["pd"] = new NAtributoCategorico("pdDistrict", new std::string(pdDistrict));
    //this->atributos["ct"] = new NAtributoCategorico("category", new std::string(category));
    this->atributos["ct"] = new NAtributoGenerico<char>("category", Categoria::obtenerIndice(category));
}

void* Crimen::obtenerAtributo(std::string nombre_atributo) {
    return this->atributos[nombre_atributo]->obtenerValor();
}

double Crimen::obtenerX() {
    return *(double*)(this->atributos["x"]->obtenerValor());
}

double Crimen::obtenerY() {
    return *(double*)(this->atributos["y"]->obtenerValor());
}

string* Crimen::obtenerPd() {
    return (std::string*)(this->atributos["pd"]->obtenerValor());
}

char Crimen::obtenerCategory() {
    return *(char*)(this->atributos["ct"]->obtenerValor());
}

double Crimen::obtenerNumerico(char c) {
    double ret;
    if (c == 'x') {
        ret = obtenerX();
    }else {
        ret = obtenerY();
    }
    return ret;
}

string Crimen::resumen() {
    std::stringstream ss;

    ss << "un crimen con X: " << this->obtenerX() << " e Y: " << this->obtenerY()
    << "en el PD " << *this->obtenerPd() << " con categoria  "
    << Categoria::obtenerNombre(this->obtenerCategory());

    return ss.str();
}

std::map<std::string, NAtributo*>* Crimen::obtenerAtributos() {
    return &this->atributos;
}
Crimen::~Crimen() {
    for (std::map<std::string, NAtributo*>::iterator it=this->atributos.begin(); it!=this->atributos.end(); it++) {
        delete it->second;
    }

    /*cout << "Deletin ..." << this->x->obtenerValor() << endl;
    delete this->x;
    delete this->y;
    delete this->pd;*/
    //delete this->pd->obtenerValor();
}
