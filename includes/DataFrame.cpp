#include "DataFrame.hpp"

#define  CSV_IO_NO_THREAD
#include "../vendor/csv.h"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>



using namespace std;

DataFrame::DataFrame() {
    this->crimenes = std::vector<Crimen*>();
    this->crimenes.reserve(25000);
}

void DataFrame::guardarEnDisco() {
    std::cout << "Guardando resultados en disco!" << std::endl;
}

void DataFrame::leerArchivo() {

    cout << "Abriendo archivo" << endl;

    io::CSVReader<9, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("data_pruebas/train.25000.csv");

    in.read_header(io::ignore_extra_column, "Dates","Category","Descript","DayOfWeek","PdDistrict","Resolution","Address","X","Y");

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

    while(in.read_row(Dates,Category,Descript,DayOfWeek,PdDistrict,Resolution,Address,X,Y)){

        Crimen* crimen = new Crimen(X,Y,PdDistrict);

        this->crimenes[c] = crimen;
        c++;

        //cout << crimen->obtenerX() << "," << crimen->obtenerY() << "," << *crimen->obtenerPd() << endl;
    }

    cout << "Leidos " << c+1 << " crimenes." << endl;
    for(std::vector<int>::size_type i = 0; i < 5; i++) {
        Crimen* crimen = this->crimenes[i];
        cout << crimen->obtenerX() << "\t" << crimen->obtenerY() << "\t" << *crimen->obtenerPd() << endl;
    }
}

DataFrame::~DataFrame() {
    for(std::vector<int>::size_type i = 0; i != this->crimenes.size(); i++) {
        delete this->crimenes[i];
    }

}
