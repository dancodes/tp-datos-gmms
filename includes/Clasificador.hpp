#pragma once

class DataFrame;

class Clasificador {
public:
    void entrenar(DataFrame* entrenamientos);
    DataFrame* predecir(DataFrame* entrenamientos);
};
