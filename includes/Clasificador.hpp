#pragma once

#include <string>
#include <vector>

class Crimen;
class DataFrame;
class TuplasCat;

class Clasificador {
public:

    virtual void entrenar(DataFrame* entrenamientos) = 0;
    virtual std::pair <TuplasCat*,int>  predecirCrimen(Crimen* crimen) = 0;
    virtual std::vector<std::pair <TuplasCat*,int>>* predecir(DataFrame* entrenamientos) = 0;
};
