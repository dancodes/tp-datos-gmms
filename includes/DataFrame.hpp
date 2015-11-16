#pragma once
#include "Crimen.hpp"
#include <vector>

using namespace std;



class DataFrame {
public:
    DataFrame();
    DataFrame(std::vector<Crimen*>* crimenes_previos);
    void guardarEnDisco();
    void leerArchivoTrain();
    void leerArchivoTest();
    void resumen();
    unsigned int cantidad();
    double infoGainPd();
    DataFrame* filtrar(std::string nombre_atributo, std::string comparador, std::string condicion);
    void borrarCrimenes();
    ~DataFrame();
private:
    std::vector<Crimen*>* crimenes;
};
