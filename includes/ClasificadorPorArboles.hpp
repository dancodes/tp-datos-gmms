#pragma once

#include "Clasificador.hpp"
#include "DataFrame.hpp"
#include "Arbol.hpp"
#include <iostream>

class ClasificadorPorArboles: public Clasificador{
public:
    void entrenar(DataFrame* entrenamientos);
    DataFrame* predecir(DataFrame* entrenamientos);
};
