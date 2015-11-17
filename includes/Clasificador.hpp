#pragma once

class DataFrame;

class Clasificador {
public:
    void entrenar(DataFrame* entrenamientos);
    double calculoInfoGainDP(DataFrame* entrenamientos);
    DataFrame* predecir(DataFrame* entrenamientos);
    double calculoInfoGainNumerico(DataFrame* entrenamientos , double comparador);
    double calculoInfoGainXoY(DataFrame* entrenamientos);
};
