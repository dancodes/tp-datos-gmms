#pragma once

#include <string>

class Crimen;
class DataFrame;

class Clasificador {
public:

    virtual void entrenar(DataFrame* entrenamientos) = 0;
    virtual std::string predecirCrimen(Crimen* crimen) = 0;
    virtual DataFrame* predecir(DataFrame* entrenamientos) = 0;
};
