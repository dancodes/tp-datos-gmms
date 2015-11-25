#pragma once

#include "Clasificador.hpp"
#include "DataFrame.hpp"
#include "Arbol.hpp"
#include "TuplasCat.hpp"
#include "Categoria.hpp"
#include <iostream>
#include <string>
#include <vector>

#include <thread>
#include <mutex>


class ClasificadorPorArboles: public Clasificador{
public:
    ClasificadorPorArboles();
    void entrenar(DataFrame* entrenamientos);
    void agregarArboles(DataFrame* entrenamientos, int cantidad);
    TuplasCat* predecirCrimen(Crimen* crimen);
    std::vector<TuplasCat*>* predecir(DataFrame* entrenamientos);
    ~ClasificadorPorArboles();
    int cantArboles;
private:
    int numeroAlAzar(int min, int max);
    char predecirCatCrimen(Crimen* crimen, int arbolID);
    std::mutex arboles_mutex;

    std::vector<Arbol*>* arboles_de_decision;
};
