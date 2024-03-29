#pragma once
#define  CSV_IO_NO_THREAD


#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

#include "Categoria.hpp"

using namespace std;

struct TuplaCat {
    string cat;
    int cant;
};

class TuplasCat {
private:
    int total;
    unsigned long vector[39];
public:

    TuplasCat() {

        for (int i=0; i<=38; i++) {
            vector[i] = 0;
        }
        this->total = 0;
    }


    void aumentarCat(string cat) {
        bool aumentado = false;

        char index = Categoria::obtenerIndice(cat);

        this->aumentarPosicion(index);
    }

    void aumentarPosicion(char i) {

        this->vector[i] = this->vector[i] + 1;
        this->total++;
    }

    int obtenerTotal() {
        return this->total;
    }

    double informationGain(char algoritmo_de_impureza) {
        double entropia = 0;

        if(total == 0) {
            return 0.0;
        } else {
            for (int i= 0; i < 39 ; i++) {
                double probabilidad = ((double)this->vector[i] / (double)this->obtenerTotal());

                if(probabilidad != 0) {

                    if(algoritmo_de_impureza == 'e') {
                        entropia = entropia + (probabilidad * log2(probabilidad));
                    } else if (algoritmo_de_impureza == 'g') {
                        entropia = entropia - (probabilidad * (1 - probabilidad));
                    }
                }
            }

            return entropia;
        }
    }


    std::vector<double>*  obtenerResultado() {
        std::vector<double>* v= new std::vector<double>();
        for (int i= 0; i<39; i++) {
            v->push_back((double)this->vector[i] / (double)total);

        }
        return v;
    }


    char mayorCrimen() {

        int cantMax = 0;
        char catMax = -1;

        for (char i = 0; i<39; i++) {
            if (this->vector[i] > cantMax) {
                cantMax = this->vector[i];

                catMax = i;
            }
        }
        return catMax;
    }

    void resumen() {

        for (char i = 0; i<39; i++) {
            if (this->vector[i] > 0) {
                std::cout <<  Categoria::obtenerNombre(i) << " con " << this->vector[i] << " votos" << std::endl;
            }
        }
    }

    int obtenerCantCat(char i) {
        return this->vector[i];
    }

    void sumarTuplas(TuplasCat* tpc) {
        for (char i=0 ; i <= 38 ; i++){
            int cantidad_a_sumar = tpc->obtenerCantCat(i);
            this->vector[i] = this->vector[i] + cantidad_a_sumar;
            this->total = this->total + cantidad_a_sumar;
        }

    }

};
