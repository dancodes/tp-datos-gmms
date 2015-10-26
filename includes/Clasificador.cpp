#include "Clasificador.hpp"
#include "DataFrame.hpp"

#include <iostream>

void Clasificador::entrenar(DataFrame* entrenamientos) {
    std::cout << "Entrenando clasificador..." << std::endl;
}

DataFrame* Clasificador::predecir(DataFrame* entrenamientos) {
    std::cout << "Prediciendo crimenes..." << std::endl;
    DataFrame* dtf = new DataFrame;
    return dtf;
}
