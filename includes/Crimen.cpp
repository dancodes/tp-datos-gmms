#include "Crimen.hpp"


#include "NAtributo.hpp"
#include "NAtributoNumerico.hpp"
#include "NAtributoCategorico.hpp"
#include "NAtributoGenerico.hpp"

using namespace std;


Crimen::Crimen(double x, double y, std::string pdDistrict, std::string DayOfWeek, std::string category) {
    this->id=-1;
    this->atributos["x"] = new NAtributoNumerico("x", x * 10e9);
    this->atributos["y"] = new NAtributoNumerico("y", y * 10e9);
    this->atributos["pdDistrict"] = new NAtributoCategorico("pdDistrict", new std::string(pdDistrict));

    if(DayOfWeek != "Saturday" && DayOfWeek != "Sunday") {
        this->atributos["finDeSemana"] = new NAtributoCategorico("finDeSemana", new std::string("0"));
    } else {
        this->atributos["finDeSemana"] = new NAtributoCategorico("finDeSemana", new std::string("1"));
    }

    //this->atributos["DayOfWeek"] = new NAtributoCategorico("DayOfWeek", new std::string(DayOfWeek));
    //this->atributos["ct"] = new NAtributoCategorico("category", new std::string(category));
    this->categoria = Categoria::obtenerIndice(category);
}
Crimen::Crimen(int Id, double x, double y, std::string pdDistrict, std::string DayOfWeek, std::string category) {
    this->id=Id;
    this->atributos["x"] = new NAtributoNumerico("x", x * 10e9);
    this->atributos["y"] = new NAtributoNumerico("y", y * 10e9);
    this->atributos["pdDistrict"] = new NAtributoCategorico("pdDistrict", new std::string(pdDistrict));

    if(DayOfWeek != "Saturday" && DayOfWeek != "Sunday") {
        this->atributos["finDeSemana"] = new NAtributoCategorico("finDeSemana", new std::string("0"));
    } else {
        this->atributos["finDeSemana"] = new NAtributoCategorico("finDeSemana", new std::string("1"));
    }

    //this->atributos["DayOfWeek"] = new NAtributoCategorico("DayOfWeek", new std::string(DayOfWeek));
    //this->atributos["ct"] = new NAtributoCategorico("category", new std::string(category));
    this->categoria = Categoria::obtenerIndice(category);
}

void* Crimen::obtenerAtributo(const std::string& nombre_atributo) {
    return this->atributos[nombre_atributo]->obtenerValor();
}

double Crimen::obtenerX() {
    return *(double*)(this->atributos["x"]->obtenerValor());
}

double Crimen::obtenerY() {
    return *(double*)(this->atributos["y"]->obtenerValor());
}

string* Crimen::obtenerPd() {
    return (std::string*)(this->atributos["pdDistrict"]->obtenerValor());
}

char Crimen::obtenerCategory() {
    return (this->categoria);
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
int Crimen::obtenerId() {
    return this->id;
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
