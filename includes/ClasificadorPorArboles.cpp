#include "ClasificadorPorArboles.hpp"
#include <iostream>
#include <random>

#include "../configuracion.h"

ClasificadorPorArboles::ClasificadorPorArboles() {
     arboles_de_decision =  new std::vector<Arbol*>();
}

void ClasificadorPorArboles::entrenar(DataFrame* entrenamientos) {
    int cantidad_de_arboles = CANTIDAD_DE_ARBOLES;

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
       TuplasCat* prediccion = this->predecirCatCrimen(crimen, i);

       if(prediccion != NULL) {
           tp->sumarTuplas(prediccion);
       }
   }
   return tp;
}


TuplasCat* ClasificadorPorArboles::predecirCatCrimen(Crimen* crimen, int arbolID) {

    TuplasCat* categoria = this->arboles_de_decision->at(arbolID)->predecir(crimen);
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


    std::queue<Crimen*> trabajos;

    for(int i = 0; i < entrenamientos->cantidad(); i++) {
        Crimen* crimen = entrenamientos->at(i);
        trabajos.push(crimen);
    }

    std::thread t[NUM_THREADS];

    for (int i=0; i < NUM_THREADS; i++) {
        t[i] = std::thread(&ClasificadorPorArboles::predecirCrimenes, this, std::ref(trabajos), resultados, std::ref(contador));
    }

    for (int i=0; i < NUM_THREADS; i++) {
        t[i].join();
    }

    /*
    if (contador % uno_por_ciento == 0 && porciento < 100) {
    //if (porciento < 100) {

        if (porciento < 10) {
            std::cout << "\b\b\b" << std::flush;
        } else {
            std::cout << "\b\b\b\b" << std::flush;
        }

        std::cout << porciento << "\%" << std::flush;
        porciento++;
    }*/


    std::cout << "Completado! " << resultados->size() << " crimenes predecidos" << std::endl;

    //std::cout << "Precision: " << contador/(entrenamientos->cantidad()) * 100.0 << "\%" << std::endl;
    return resultados;
}


void ClasificadorPorArboles::predecirCrimenes(std::queue<Crimen*>& trabajos, std::vector<TuplasCat*>* resultados, int& contador) {

    Crimen* crimen_actual;
    std::vector<TuplasCat*> predicciones;
    bool continuar = true;

    std::vector<TuplasCat*> buffer;

    while(continuar) {

        {
            std::lock_guard<std::recursive_mutex> guard(this->arboles_mutex);

            if(trabajos.size() > 0) {
                crimen_actual = trabajos.front(); //Consigue el siguiente elemento de la cola
                trabajos.pop(); //Borra dicho elemento de la cola
            } else {
                continuar = false;

                //Devolvemos el resto del buffer
                std::lock_guard<std::recursive_mutex> guard(this->resultados_mutex);

                for(int i = 0; i <buffer.size(); i++) {
                    resultados->push_back(buffer.at(i));
                }
            }
        }

        if(continuar) {
            TuplasCat* prediccion = this->predecirCrimen(crimen_actual);
            buffer.push_back(prediccion);
            {
                std::lock_guard<std::recursive_mutex> guard(this->resultados_mutex);
                contador = contador+1;

                if (contador % 50000 == 0) {
                    for(int i = 0; i <buffer.size(); i++) {
                        resultados->push_back(buffer.at(i));
                    }
                    std::cout << contador << "!" << std::endl;

                    buffer.clear();
                }
            }


        }
    }
}

ClasificadorPorArboles::~ClasificadorPorArboles() {
    delete this->arboles_de_decision;
}
