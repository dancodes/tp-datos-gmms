#include "ClasificadorPorArboles.hpp"
#include <iostream>
#include <random>


ClasificadorPorArboles::ClasificadorPorArboles() {

}

void ClasificadorPorArboles::entrenar(DataFrame* entrenamientos) {

    std::cout << "[EN PROGRESO] Entrenando clasificador..." << std::endl << std::endl; //Nach0 es un poco mas Crudo que Dani
    Arbol arbolito(entrenamientos);
}

TuplasCat* ClasificadorPorArboles::predecirCrimen(Crimen* crimen) {

    int numero_al_azar = this->numeroAlAzar(0,39);

    TuplasCat* tp = new TuplasCat();
    tp->aumentarPosicion(numero_al_azar);

    return tp;
}


int ClasificadorPorArboles::numeroAlAzar(int min, int max) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 39); // define the range

    return distr(eng);
}


std::vector<TuplasCat*>* ClasificadorPorArboles::predecir(DataFrame* entrenamientos) {
    //std::cout << "[TODO] Prediciendo crimenes..." << std::endl;
    std::cout << "[EN PROGRESO] Prediciendo para el ojete..." << std::endl;

    std::vector<TuplasCat*>* resultados = new std::vector<TuplasCat*>();

    for(int i = 0; i < entrenamientos->cantidad(); i++) {
        Crimen* crimen = entrenamientos->at(i);


        TuplasCat* prediccion = this->predecirCrimen(crimen);

        resultados->push_back(prediccion);

        std::cout << "Prediccion: " << prediccion << std::endl;
    }

    return resultados;
}
