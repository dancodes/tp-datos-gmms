#include "DataFrame.hpp"
#include "TuplasCat.hpp"
#include "Clasificador.hpp"
#define  CSV_IO_NO_THREAD
#include "../vendor/csv.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <ctime>
#include <iomanip>

#include "../configuracion.h"

extern unsigned long long int dataframes_creados;
extern unsigned long long int nodos_creados;
extern unsigned long long int misses;

using namespace std;

DataFrame::DataFrame() {
    this->crimenes = new std::vector<Crimen*>();
    this->crimenes->reserve(25000);
    dataframes_creados++;
}

DataFrame::DataFrame(std::vector<Crimen*>* crimenes_filtrados) {
    this->crimenes = crimenes_filtrados;
    dataframes_creados++;
}


void DataFrame::leerArchivoTrain() {

    cout << "Abriendo archivo Train" << endl;

    typedef io::CSVReader<9, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> csv;


    //csv in("data_pruebas/train.10.csv");
    //csv in("data_pruebas/train.100.csv");
    //csv in("data_pruebas/train.1000.csv");
    //csv in("data_pruebas/train.25000.csv");
    //csv in("data_pruebas/train.5.noentropy.csv");
    //csv in("data_pruebas/train.10.variando.el.PD");
    //csv in("data_pruebas/train.10.variando.el.X");

    //csv in("data/train.csv");

    csv in(NOMBRE_CSV_TRAIN);

    in.read_header(io::ignore_extra_column,"Dates","Category","Descript","DayOfWeek","PdDistrict","Resolution","Address","X","Y");

    string Dates;
    string Category;
    string Descript;
    string DayOfWeek;
    string PdDistrict;
    string Resolution;
    string Address;
    double X;
    double Y;

    cout.precision(15);

    unsigned int c = 0;

    while(in.read_row(Dates,Category,Descript,DayOfWeek,PdDistrict,Resolution,Address,X,Y)) {
        if ( X>-123  && X<-121  && Y>36  && Y<38  ) {


            Crimen* crimen = new Crimen(X,Y,PdDistrict,DayOfWeek,Category);

            this->crimenes->push_back(crimen);

            c++;

            if( c % 50000 == 0) {
                cout << "Leidos " << c << " crimenes." << endl;
            }
        }

    }

    cout << "Leidos " << c+1 << " crimenes." << endl << endl;


}
void DataFrame::leerArchivoTest() {

    cout << "Abriendo archivo Test" << endl;

    typedef io::CSVReader<7, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> csv;


    //csv in("data/test.csv");
    //csv in("data_pruebas/test.5000.csv");
    //csv in("data_pruebas/test.10.csv");

    csv in(NOMBRE_CSV_TEST);

    in.read_header(io::ignore_extra_column,"Id","Dates","DayOfWeek","PdDistrict","Address","X","Y");

    string Dates;
    int Id;
    string DayOfWeek;
    string PdDistrict;
    string Address;
    double X;
    double Y;

    cout.precision(15);

    unsigned int c = 0;

    std::string categoria_no_definida("WARRANTS");

    while(in.read_row(Id,Dates,DayOfWeek,PdDistrict,Address,X,Y)) {

        Crimen* crimen = new Crimen(Id,X,Y,PdDistrict,DayOfWeek,categoria_no_definida);

        this->crimenes->push_back(crimen);

        c++;

        if( c % 50000 == 0) {
            cout << "Leidos " << c << " crimenes." << endl;
        }

    }

    cout << "Leidos " << c+1 << " crimenes." << endl << endl;


}
void DataFrame::resumen() {
    //Loop para mostrar los top 5 en la pantalla

    cout << endl << "DataFrame: " << this->crimenes->size() << " elementos" << endl;
    cout << "X" << "\t\t\t" << "Y" << "\t\t\t" << "PdDistrict" << "\t" << "Category" << endl;
    cout << "=================================================================================" << endl;

    std::vector<Crimen*>::iterator it;
    it = this->crimenes->begin();



    for(std::vector<int>::size_type i = 0; (i < this->crimenes->size()) && (i < 5); i++) {
        Crimen* crimen = (*this->crimenes)[i];
        cout << crimen->obtenerX() << "\t" << crimen->obtenerY() << "\t"
             << *crimen->obtenerPd() << "\t" << Categoria::obtenerNombre(crimen->obtenerCategory()) << endl;
    }

    //cout << endl << "[DANIEL] Ganancia de Información de PdDistrict: " << this->infoGainPd() << endl;

    /*Clasificador clf;
    cout << endl << "[MATI] Ganancia de Información de PdDistrict: " <<
            clf.calculoInfoGainDP(this) << endl << endl;*/
}

unsigned int DataFrame::cantidad() {
    return this->crimenes->size();
}

Crimen* DataFrame::at(int i) {
    return (*this->crimenes)[i];
}

TuplasCat* DataFrame::generarProbabilidades() {

    TuplasCat* probabilidades = new TuplasCat();

    for(int i = 0; i < this->cantidad(); i++) {
        Crimen* crimen = this->at(i);
        char categoria = crimen->obtenerCategory();

        probabilidades->aumentarPosicion(categoria);
    }

    return probabilidades;
}

std::vector<std::string>* DataFrame::obtenerPosiblesOpciones(std::string nombre_atributo) {
    std::map<std::string,unsigned int> diccAtrib = std::map<std::string,unsigned int>();
    std::vector<std::string>* listaAtributos = new std::vector<std::string>();

    for(int i = 0; i < this->cantidad(); i++) {
        Crimen* actual = this->at(i);
        std::string atributo_actual = *(std::string*)actual->obtenerAtributo(nombre_atributo);
        if(diccAtrib.count(atributo_actual)==0) {
            diccAtrib[atributo_actual]=1;
            listaAtributos->push_back(atributo_actual);
        }
    }
    return listaAtributos;
}

DataFrame* DataFrame::filtrar(CriterioNodo& criterio) {

    std::vector<Crimen*>* crimenes_filtrados = new std::vector<Crimen*>();

    int c = 0  ;


    for(std::vector<int>::size_type i = 0; i < this->crimenes->size(); i++) {

        Crimen* actual = (this->crimenes->at(i));

        if(this->cumpleCondicion(actual, criterio)) {
            crimenes_filtrados->push_back(actual);
        }

        c++;

        /*if( c % 50000 == 0) {
            cout << "Filtrados " << c << " crimenes." << endl;
        }*/
    }

    DataFrame* nueva_df = new DataFrame(crimenes_filtrados);

    return nueva_df;
}

bool DataFrame::cumpleCondicion(Crimen* actual, CriterioNodo& criterio) {

    std::string* nombre_atributo = criterio.obtenerAtributo();
    std::string* comparador = criterio.obtenerComparador();

    if(nombre_atributo->compare("x") == 0 || nombre_atributo->compare("y") == 0) {

        //double condicion_double = std::stod(condicion);

        double condicion_double = criterio.obtenerCondicionNumerica();

        double valor_actual = *(double*)(actual->obtenerAtributo(*nombre_atributo));

        if(comparador->compare("<=") == 0) {
            if(valor_actual <= condicion_double) {
                return true;
            }
        } else if(comparador->compare(">") == 0) {
            if(valor_actual > condicion_double) {
                return true;
            }
        }

    } else {
        // comparador es irrelevante acá
        std::string* condicion = criterio.obtenerCondicion();

        std::string* pd_actual = (std::string*)(actual->obtenerAtributo(*nombre_atributo));

        if(condicion->compare(*pd_actual) == 0) {
            return true;
        }
    }

    return false;
}

void DataFrame::borrarCrimenes() {
    for(std::vector<int>::size_type i = 0; i != this->crimenes->size(); i++) {
        delete (*this->crimenes)[i];
    }
}

DataFrame::~DataFrame() {
    delete this->crimenes;
    dataframes_creados--;
}

DataFrame* DataFrame::obtenerCrimenes() {
    std::vector<Crimen*>* crimenesAux = new std::vector<Crimen*>();

    int cantidad = this->numeroAlAzar(1, this->cantidad() / 4);



    std::vector<int> numeros = this->numerosAlAzar(0, cantidad - 1, cantidad);

    for (int i=0; i < numeros.size(); i++) {
        int azar = numeros.at(i);

        crimenesAux->push_back(this->crimenes->at(azar));
    }

    DataFrame* df = new DataFrame(crimenesAux);
    return df;
}


int DataFrame::numeroAlAzar(unsigned int min, unsigned int max) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max); // define the range

    return distr(eng);
}

std::vector<int> DataFrame::numerosAlAzar(unsigned int min, unsigned int max, unsigned int cantidad) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max); // define the range

    std::vector<int> numeros;

    for(int i=0; i<cantidad; i++) {
        numeros.push_back(distr(eng));
    }

    return numeros;
}
