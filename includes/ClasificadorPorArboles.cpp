#include "ClasificadorPorArboles.hpp"
#include <iostream>
#include <random>
#include <utility>

#include "../configuracion.h"

ClasificadorPorArboles::ClasificadorPorArboles() {
    arboles_de_decision =  new std::vector<Arbol*>();
    this->profundidad = -1;
    this->algoritmo_de_impureza = 'e';
}

ClasificadorPorArboles::ClasificadorPorArboles(int profundidad, char algoritmo_de_impureza) {
    arboles_de_decision =  new std::vector<Arbol*>();
    this->profundidad = profundidad;
    this->algoritmo_de_impureza = algoritmo_de_impureza;
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

        Arbol* arbolNavidad = new Arbol(subconjunto, this->profundidad, this->algoritmo_de_impureza, true);


        std::lock_guard<std::recursive_mutex> guard(this->arboles_mutex);
        std::cout << "Creado arbol #" << i << ": " << subconjunto->cantidad() << " elementos" << std::endl;
        this->arboles_de_decision->push_back(arbolNavidad);
    }
}

std::pair <TuplasCat*,int> ClasificadorPorArboles::predecirCrimen(Crimen* crimen) {
    TuplasCat* tp = new TuplasCat();
   //int numero_al_azar = this->numeroAlAzar(0,39);

   for (int i= 0 ; i < this->arboles_de_decision->size(); i++){

       //tp->aumentarPosicion(numero_al_azar);
       TuplasCat* prediccion = this->predecirCatCrimen(crimen, i);

       if(prediccion != NULL) {
           tp->sumarTuplas(prediccion);
       }
   }
   std::pair <TuplasCat*,int> tuplaPredic (tp,crimen->obtenerId());
   return tuplaPredic;
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


std::vector<std::pair <TuplasCat*,int>>* ClasificadorPorArboles::predecir(DataFrame* entrenamientos) {
    //std::cout << "[TODO] Prediciendo crimenes..." << std::endl;
    std::cout << "[EN PROGRESO] Prediciendo para el ojete..." << std::endl;

    std::vector<std::pair <TuplasCat*,int>>* resultados = new std::vector<std::pair <TuplasCat*,int>>();

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


void ClasificadorPorArboles::predecirCrimenes(std::queue<Crimen*>& trabajos, std::vector<std::pair <TuplasCat*,int>>* resultados , int& contador) {

    Crimen* crimen_actual;
//    std::vector<TuplasCat*> predicciones;
    bool continuar = true;

    std::vector< std::pair <TuplasCat*,int>> buffer;

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
               std::pair <TuplasCat*,int> tuplaPredic  = this->predecirCrimen(crimen_actual);
            buffer.push_back(tuplaPredic);
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


void ClasificadorPorArboles::guardarEnDisco(std::vector<std::pair <TuplasCat*,int>>* vectTupl) {

    std::vector<std::vector<double>>  vProb;
    std::vector<int>  vId;
    for (int j=0 ; j<vectTupl->size();j++) {


//        std::pair <std::string,double> tupla;

//        tupla= make_pair (*vectTupl)[j].first, ;  //pair
        TuplasCat* tupCat = (((*vectTupl)[j]).first);
        int id = (((*vectTupl)[j]).second);

        vProb.push_back(*(tupCat->obtenerResultado()));
        vId.push_back(id);
    }

    std::cout << "[TODO] Guardando resultados en disco!" << std::endl;
    ofstream myfile;

    std::time_t tiempo_unix = std::time(nullptr);
    std::stringstream ss;
    ss << "data/resultados." << tiempo_unix << ".arboles"
       << CANTIDAD_DE_ARBOLES*NUM_THREADS
       << ".profundidad" << this->profundidad
       << ".algoritmo_" << this->algoritmo_de_impureza
       << ".csv";
    myfile.open (ss.str());


    myfile <<"Id,ARSON,ASSAULT,BAD CHECKS,BRIBERY,BURGLARY,DISORDERLY CONDUCT,DRIVING UNDER THE INFLUENCE,";
    myfile <<"DRUG/NARCOTIC,DRUNKENNESS,EMBEZZLEMENT,EXTORTION,FAMILY OFFENSES,FORGERY/COUNTERFEITING,FRAUD,GAMBLING,KIDNAPPING,LARCENY/THEFT,";
    myfile <<"LIQUOR LAWS,LOITERING,MISSING PERSON,NON-CRIMINAL,OTHER OFFENSES,PORNOGRAPHY/OBSCENE MAT,PROSTITUTION,RECOVERED VEHICLE,ROBBERY,";
    myfile <<"RUNAWAY,SECONDARY CODES,SEX OFFENSES FORCIBLE,SEX OFFENSES NON FORCIBLE,STOLEN PROPERTY,SUICIDE,SUSPICIOUS OCC,";
    myfile <<"TREA,TRESPASS,VANDALISM,VEHICLE THEFT,WARRANTS,WEAPON LAWS\n";

    for (int j=0 ; j<vProb.size();j++) {

        //Id
        myfile << vId[j];
        myfile << ",";
        for(int i = 0; i < vProb[j].size(); i++) {

            //Probabilidad
            myfile << vProb[j][i];

            if(i != (vProb[j].size() - 1)) {
                myfile << ",";
            }
        }
        myfile << "\n" ;

    }

    myfile.close();
}

ClasificadorPorArboles::~ClasificadorPorArboles() {
    delete this->arboles_de_decision;
}
