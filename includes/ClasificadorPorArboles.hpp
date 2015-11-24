#pragma once

#include "Clasificador.hpp"
#include "DataFrame.hpp"
#include "Arbol.hpp"
#include "TuplasCat.hpp"
#include "Categoria.hpp"
#include <iostream>
#include <string>
#include <vector>


class ClasificadorPorArboles: public Clasificador{
public:
    ClasificadorPorArboles();
    void entrenar(DataFrame* entrenamientos);
    TuplasCat* predecirCrimen(Crimen* crimen);
    std::vector<TuplasCat*>* predecir(DataFrame* entrenamientos);
    ~ClasificadorPorArboles();
    int cantArboles;
private:
    int numeroAlAzar(int min, int max);
    std::string predecirCatCrimen(Crimen* crimen, int arbolID);

    std::vector<Arbol*>* arboles_de_decision;
};
