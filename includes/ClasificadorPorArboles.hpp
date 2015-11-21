#pragma once

#include "Clasificador.hpp"
#include "DataFrame.hpp"
#include "Arbol.hpp"
#include <iostream>
#include <string>

class ClasificadorPorArboles: public Clasificador{
public:
    ClasificadorPorArboles();
    void entrenar(DataFrame* entrenamientos);
    std::string predecirCrimen(Crimen* crimen);
    DataFrame* predecir(DataFrame* entrenamientos);
private:
    int numeroAlAzar(int min, int max);
};
