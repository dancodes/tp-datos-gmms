#pragma once

#include <string>
#include <vector>

class Crimen;
class DataFrame;
class TuplasCat;

class Clasificador {
public:

    virtual void entrenar(DataFrame* entrenamientos) = 0;
    virtual TuplasCat* predecirCrimen(Crimen* crimen) = 0;
    virtual std::vector<TuplasCat*>* predecir(DataFrame* entrenamientos) = 0;
};
