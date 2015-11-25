#pragma once

#include "Clasificador.hpp"
#include "DataFrame.hpp"
#include "Arbol.hpp"
#include "TuplasCat.hpp"
#include "Categoria.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>

#include <thread>
#include <mutex>


class ClasificadorPorArboles: public Clasificador{
public:
    ClasificadorPorArboles();
    void entrenar(DataFrame* entrenamientos);
    void agregarArboles(DataFrame* entrenamientos, int cantidad);
    void predecirCrimenes(std::queue<Crimen*>& trabajos, std::vector<TuplasCat*>* resultados, int& contador);
    TuplasCat* predecirCrimen(Crimen* crimen);
    std::vector<TuplasCat*>* predecir(DataFrame* entrenamientos);
    ~ClasificadorPorArboles();
    int cantArboles;
private:
    int numeroAlAzar(int min, int max);
    TuplasCat* predecirCatCrimen(Crimen* crimen, int arbolID);
    std::recursive_mutex arboles_mutex;
    std::recursive_mutex resultados_mutex;

    std::vector<Arbol*>* arboles_de_decision;
};
