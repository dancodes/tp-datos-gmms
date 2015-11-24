#include "ClasificadorPorArboles.hpp"
#include <iostream>
#include <random>


ClasificadorPorArboles::ClasificadorPorArboles() {
     arboles_de_decision =  new std::vector<Arbol*>();

}

void ClasificadorPorArboles::entrenar(DataFrame* entrenamientos) {
    int cantidad_de_arboles = 10;

    int crimenes_por_arbol = entrenamientos->cantidad();

    std::cout << "[EN PROGRESO] Entrenando " << cantidad_de_arboles << " arboles para el clasificador..." << std::endl; //Nach0 es un poco mas Crudo que Dani
    for (int i=0; i < cantidad_de_arboles; i++) {
        //std::cout << i << std::endl;
        Arbol* arbolNavidad = new Arbol(entrenamientos->obtenerCrimenes(crimenes_por_arbol));
        this->arboles_de_decision->push_back(arbolNavidad);
    }
}

TuplasCat* ClasificadorPorArboles::predecirCrimen(Crimen* crimen) {
    TuplasCat* tp = new TuplasCat();
    //int numero_al_azar = this->numeroAlAzar(0,39);
    for (int i= 0 ; i < this->arboles_de_decision->size() ; i++){

        //tp->aumentarPosicion(numero_al_azar);
        tp->aumentarCat(predecirCatCrimen(crimen, i));
    }
    return tp;
}


std::string ClasificadorPorArboles::predecirCatCrimen(Crimen* crimen, int arbolID){
    char categoria = this->arboles_de_decision->at(arbolID)->Predecir(crimen);
    return Categoria::obtenerNombre(categoria);
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
    double contador = 0.0;

    for(int i = 0; i < entrenamientos->cantidad(); i++) {
        Crimen* crimen = entrenamientos->at(i);//probando


        TuplasCat* prediccion = this->predecirCrimen(crimen);

        resultados->push_back(prediccion);
        //prediccion->resumen();

        //std::cout << "Prediccion: " << prediccion->mayorCrimen() << std::endl;
        if((entrenamientos->at(i)->obtenerCategory()) == prediccion->mayorCrimen()){
            contador = contador+1;
        }
    }

    std::cout << "Precision: " << contador/(entrenamientos->cantidad()) * 100.0 << "\%" << std::endl;
    return resultados;
}

ClasificadorPorArboles::~ClasificadorPorArboles() {
    delete this->arboles_de_decision;
}
