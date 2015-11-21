#include "ClasificadorPorArboles.hpp"
#include <iostream>
#include <random>
#include "TuplasCat.hpp"

ClasificadorPorArboles::ClasificadorPorArboles() {

}

void ClasificadorPorArboles::entrenar(DataFrame* entrenamientos) {

    std::cout << "[EN PROGRESO] Entrenando clasificador..." << std::endl << std::endl; //Nach0 es un poco mas Crudo que Dani
    Arbol arbolito(entrenamientos);
}

std::string ClasificadorPorArboles::predecirCrimen(Crimen* crimen) {

    int numero_al_azar = this->numeroAlAzar(0,39);

    TuplasCat* tp = new TuplasCat();
    tp->aumentarPosicion(numero_al_azar);

    return tp->mayorCrimen();
}


int ClasificadorPorArboles::numeroAlAzar(int min, int max) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 39); // define the range

    return distr(eng);
}


DataFrame* ClasificadorPorArboles::predecir(DataFrame* entrenamientos) {
    //std::cout << "[TODO] Prediciendo crimenes..." << std::endl;
    std::cout << "[EN PROGRESO] Prediciento para el ojete..." << std::endl << std::endl;

    for(int i = 0; i < 5; i++) {
        Crimen* crimen = entrenamientos->at(i);
        std::string prediccion = this->predecirCrimen(crimen);
        std::cout << "Prediccion: " << prediccion << std::endl;
    }


    DataFrame* dtf = new DataFrame;
    return dtf;
}
