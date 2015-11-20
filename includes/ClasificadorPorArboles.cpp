#include "ClasificadorPorArboles.hpp"
#include <iostream>

void ClasificadorPorArboles::entrenar(DataFrame* entrenamientos) {
    std::cout << "[EN PROGRESO] Entrenando clasificador..." << std::endl; //Nach0 es un poco mas Crudo que Dani

    Arbol arbolito(entrenamientos);


}


DataFrame* ClasificadorPorArboles::predecir(DataFrame* entrenamientos) {
    std::cout << "[TODO] Prediciendo crimenes..." << std::endl;
    DataFrame* dtf = new DataFrame;
    return dtf;
}
