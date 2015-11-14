#include "DataFrame.hpp"

#define  CSV_IO_NO_THREAD
#include "../vendor/csv.h"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

using namespace std;

DataFrame::DataFrame() {
    this->crimenes = new std::vector<Crimen*>();
    this->crimenes->reserve(25000);
}

DataFrame::DataFrame(std::vector<Crimen*>* crimenes_previos) {
    this->crimenes = crimenes_previos;
}

void DataFrame::guardarEnDisco() {
    std::cout << "Guardando resultados en disco!" << std::endl;
}

void DataFrame::leerArchivo() {

    cout << "Abriendo archivo" << endl;

    io::CSVReader<9, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("data_pruebas/train.25000.csv");

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

    std::vector<Crimen*>::iterator it;

    it = this->crimenes->begin();

    while(in.read_row(Dates,Category,Descript,DayOfWeek,PdDistrict,Resolution,Address,X,Y)){

        Crimen* crimen = new Crimen(X,Y,PdDistrict);

        this->crimenes->insert(it,crimen);

        c++;

        //cout << crimen->obtenerX() << "," << crimen->obtenerY() << "," << *crimen->obtenerPd() << endl;
    }

    cout << "Leidos " << c+1 << " crimenes." << endl;

    //Loop para mostrar los top 5 en la pantalla

    for(std::vector<int>::size_type i = 0; i < 3; i++) {
        Crimen* crimen = (*this->crimenes)[i];
        cout << crimen->obtenerX() << "\t" << crimen->obtenerY() << "\t" << *crimen->obtenerPd() << endl;
    }


    cout << "Ganancia de Información de PdDistrict: " << this->infoGainPd() << endl;
}

unsigned int DataFrame::cantidad() {
    return this->crimenes->size();
}

double DataFrame::infoGainPd() {


    std::map<string, unsigned int> frequencia_de_clase = std::map<string, unsigned int>();

    for(std::vector<int>::size_type i = 0; i < this->crimenes->size(); i++) {

        Crimen* actual = (*this->crimenes)[i];
        std::string pd_actual = *actual->obtenerPd();

        if(frequencia_de_clase.count(pd_actual) == 0) {

            frequencia_de_clase[pd_actual] = 1;

        } else {

            int freq_actual = frequencia_de_clase[pd_actual];
            frequencia_de_clase[pd_actual] = freq_actual + 1;
        }
    }

    double info_gain = 0;

    // show content:
    for (std::map<string, unsigned int>::iterator it=frequencia_de_clase.begin(); it!=frequencia_de_clase.end(); ++it) {
        unsigned int freq_ci = it->second;

        info_gain = info_gain +
        (((double)freq_ci/(double)this->cantidad()) *
        log2((double)freq_ci/(double)this->cantidad()));

    }

    info_gain = info_gain * (-1.0);


    return info_gain;
}

DataFrame::~DataFrame() {
    for(std::vector<int>::size_type i = 0; i != this->crimenes->size(); i++) {
        delete (*this->crimenes)[i];
    }

    delete this->crimenes;
}
