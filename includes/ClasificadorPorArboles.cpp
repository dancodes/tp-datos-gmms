#include "ClasificadorPorArboles.hpp"
#include <iostream>
#include <random>

#define NUM_THREADS 4


ClasificadorPorArboles::ClasificadorPorArboles() {
     arboles_de_decision =  new std::vector<Arbol*>();
}

void ClasificadorPorArboles::entrenar(DataFrame* entrenamientos) {
    int cantidad_de_arboles = 25;

    std::thread t[NUM_THREADS];

    std::cout << "[EN PROGRESO] Entrenando " << cantidad_de_arboles << " arboles para el clasificador..." << std::endl; //Nach0 es un poco mas Crudo que Dani
    for (int i=0; i < NUM_THREADS; i++) {
        t[i] = std::thread(&ClasificadorPorArboles::agregarArboles, this, entrenamientos, cantidad_de_arboles);
    }

    for (int i=0; i < NUM_THREADS; i++) {
        t[i].join();
    }

    std::cout << "[TERMINADO]" << std::endl;
}

void ClasificadorPorArboles::agregarArboles(DataFrame* entrenamientos, int cantidad) {
    for (int i = 0; i<cantidad; i++) {

        DataFrame* subconjunto = entrenamientos->obtenerCrimenes();

        Arbol* arbolNavidad = new Arbol(subconjunto);


        std::lock_guard<std::recursive_mutex> guard(this->arboles_mutex);
        std::cout << "Creado arbol #" << i << ": " << subconjunto->cantidad() << " elementos" << std::endl;
        this->arboles_de_decision->push_back(arbolNavidad);
    }
}

TuplasCat* ClasificadorPorArboles::predecirCrimen(Crimen* crimen) {
    TuplasCat* tp = new TuplasCat();
    //int numero_al_azar = this->numeroAlAzar(0,39);

    for (int i= 0 ; i < this->arboles_de_decision->size(); i++){

        //tp->aumentarPosicion(numero_al_azar);
        char prediccion = this->predecirCatCrimen(crimen, i);

        if(prediccion != (char)(-1)) {
            tp->aumentarPosicion(prediccion);
        }
    }
    return tp;
}


char ClasificadorPorArboles::predecirCatCrimen(Crimen* crimen, int arbolID) {

    char categoria = this->arboles_de_decision->at(arbolID)->predecir(crimen);
    return categoria;
}

int ClasificadorPorArboles::numeroAlAzar(int min, int max) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 38); // define the range

    return distr(eng);
}


std::vector<TuplasCat*>* ClasificadorPorArboles::predecir(DataFrame* entrenamientos) {
    //std::cout << "[TODO] Prediciendo crimenes..." << std::endl;
    std::cout << "[EN PROGRESO] Prediciendo para el ojete..." << std::endl;

    std::vector<TuplasCat*>* resultados = new std::vector<TuplasCat*>();

    int cantidad_a_predecir = entrenamientos->cantidad();


    int contador = 0;

    int uno_por_ciento = cantidad_a_predecir / 100;

    int porciento = 1;

    std::cout << "Total a predecir: " << entrenamientos->cantidad() << std::endl;

    std::cout << porciento << "\% " << std::flush;

    for(int i = 0; i < entrenamientos->cantidad(); i++) {
        Crimen* crimen = entrenamientos->at(i);//probando

        //std::cout << "Prediciendo " << crimen->resumen() << std::endl;


        TuplasCat* prediccion = this->predecirCrimen(crimen);

        resultados->push_back(prediccion);

        contador = contador+1;

        if (contador % uno_por_ciento == 0 && porciento < 100) {

            if (porciento < 10) {
                std::cout << "\b\b\b" << std::flush;
            } else {
                std::cout << "\b\b\b\b" << std::flush;
            }

            std::cout << porciento << "\%" << std::flush;
            porciento++;
        }
    }

    std::cout << "Completado!" << std::endl;

    //std::cout << "Precision: " << contador/(entrenamientos->cantidad()) * 100.0 << "\%" << std::endl;
    return resultados;
}

ClasificadorPorArboles::~ClasificadorPorArboles() {
    delete this->arboles_de_decision;
}
