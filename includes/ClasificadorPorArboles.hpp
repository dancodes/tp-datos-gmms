#pragma once

#include "Clasificador.hpp"
#include "DataFrame.hpp"
#include "Arbol.hpp"
#include "TuplasCat.hpp"
#include <iostream>
#include <string>
#include <vector>


class ClasificadorPorArboles: public Clasificador{
public:
    ClasificadorPorArboles();
    void entrenar(DataFrame* entrenamientos);
    TuplasCat* predecirCrimen(Crimen* crimen);
    std::vector<TuplasCat*>* predecir(DataFrame* entrenamientos);
private:
    int numeroAlAzar(int min, int max);
    std::string predecirCatCrimen(Crimen* crimen);
    Arbol* arbol_de_decision;
};
