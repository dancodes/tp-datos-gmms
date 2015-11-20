#include "Clasificador.hpp"
#include "DataFrame.hpp"
#include "TuplasCat.hpp"
#include <iostream>

void Clasificador::entrenar(DataFrame* entrenamientos) {
    std::cout << "[EN PROGRESO] Entrenando clasificador..." << std::endl; //Nach0 es un poco mas Crudo que Dani
}


DataFrame* Clasificador::predecir(DataFrame* entrenamientos) {
    std::cout << "[TODO] Prediciendo crimenes..." << std::endl;
    DataFrame* dtf = new DataFrame;
    return dtf;
}
