#pragma once
#include "Crimen.hpp"
#include <vector>
#include "TuplasCat.hpp"
using namespace std;



class DataFrame {
public:
    DataFrame();
    DataFrame(std::vector<Crimen*>* crimenes_previos);
    void guardarEnDisco(std::vector<TuplasCat*>* tc);
    void leerArchivoTrain();
    void leerArchivoTest();
    void resumen();
    unsigned int cantidad();
    Crimen* at(int i);
    double infoGainPd();
    DataFrame* filtrar(std::string nombre_atributo, std::string comparador, std::string condicion);
    bool cumpleCondicion(Crimen* actual, std::string nombre_atributo,
                                std::string comparador, std::string condicion);
    void borrarCrimenes();
    ~DataFrame();
private:
    std::vector<Crimen*>* crimenes;
};
