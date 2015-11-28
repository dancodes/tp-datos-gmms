#pragma once
#include "Crimen.hpp"
#include <vector>
#include "TuplasCat.hpp"
#include "CriterioNodo.hpp"

using namespace std;

class DataFrame {
public:
    DataFrame();
    DataFrame(std::vector<Crimen*>* crimenes_previos);
    void leerArchivoTrain();
    void leerArchivoTest();
    void resumen();
    unsigned int cantidad();
    Crimen* at(int i);
    DataFrame* obtenerCrimenes();

    int numeroAlAzar(unsigned int min, unsigned int max);
    std::vector<int> numerosAlAzar(unsigned int min, unsigned int max, unsigned int cantidad);

    std::vector<std::string>* obtenerPosiblesOpciones(std::string nombre_atributo);
    TuplasCat* generarProbabilidades();
    //DataFrame* filtrar(std::string nombre_atributo, std::string comparador, std::string condicion);
    DataFrame* filtrar(CriterioNodo& criterio);
    bool cumpleCondicion(Crimen* actual, CriterioNodo& criterio);
    /*bool cumpleCondicion(Crimen* actual, std::string nombre_atributo,
                                std::string comparador, std::string condicion);*/
    void borrarCrimenes();
    ~DataFrame();
private:
    std::vector<Crimen*>* crimenes;
};
