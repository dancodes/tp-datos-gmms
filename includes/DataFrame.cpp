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


using namespace std;

DataFrame::DataFrame() {
    this->crimenes = new std::vector<Crimen*>();
    this->crimenes->reserve(25000);
}

DataFrame::DataFrame(std::vector<Crimen*>* crimenes_filtrados) {
    this->crimenes = crimenes_filtrados;
}

void DataFrame::guardarEnDisco(std::vector<std::vector<double>> v) {  //guarda una linea de resultados y el encabezado, flata hacerlo para mas lineas

    std::cout << "[TODO] Guardando resultados en disco!" << std::endl;
    ofstream myfile;
    myfile.open ("data/resultados.csv");


    myfile <<"WARRANTS,OTHER OFFENSES,LARCENY/THEFT,VEHICLE THEFT,VANDALISM,";
    myfile <<"NON-CRIMINAL,ROBBERY,ASSAULT,WEAPON LAWS,BURGLARY,SUSPICIOUS OCC,DRUNKENNESS,";
    myfile <<"FORGERY/COUNTERFEITING,DRUG/NARCOTIC,STOLEN PROPERTY,SECONDARY CODES,TRESPASS,";
    myfile <<"MISSING PERSON,FRAUD,KIDNAPPING,RUNAWAY,DRIVING UNDER THE INFLUENCE,";
    myfile <<"SEX OFFENSES FORCIBLE,PROSTITUTION,DISORDERLY CONDUCT,ARSON,FAMILY OFFENSES,";
    myfile <<"LIQUOR LAWS,BRIBERY,EMBEZZLEMENT,SUICIDE,LOITERING,SEX OFFENSES NON FORCIBLE,";
    myfile <<"EXTORTION,GAMBLING,BAD CHECKS,TREA,RECOVERED VEHICLE,PORNOGRAPHY/OBSCENE MAT\n";
    for (int j=0 ; j<v.size();j++){

        for(int i = 0; i < v[j].size(); i++){
            myfile << v[j][i]<< "," ;
        }
        myfile << "\n" ;

    }
    myfile.close();
}

void DataFrame::leerArchivoTrain() {

    cout << "Abriendo archivo Train" << endl;

    //io::CSVReader<9, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("data/train.csv");
    io::CSVReader<9, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("data_pruebas/train.25000.csv");
    //io::CSVReader<9, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("data_pruebas/train.5.noentropy.csv");

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

    while(in.read_row(Dates,Category,Descript,DayOfWeek,PdDistrict,Resolution,Address,X,Y)){
        if ( X>-123  && X<-121  && Y>36  && Y<38  ){


            Crimen* crimen = new Crimen(X,Y,PdDistrict,Category);

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

    //io::CSVReader<9, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("data_pruebas/train.25000.csv");
    io::CSVReader<7, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("data/test.csv");

    in.read_header(io::ignore_extra_column,"Id","Dates","DayOfWeek","PdDistrict","Address","X","Y");

    string Dates;
    string Id;
    string DayOfWeek;
    string PdDistrict;
    string Address;
    double X;
    double Y;

    cout.precision(15);

    unsigned int c = 0;

    while(in.read_row(Id,Dates,DayOfWeek,PdDistrict,Address,X,Y)){

        Crimen* crimen = new Crimen(X,Y,PdDistrict);

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
             << *crimen->obtenerPd() << "\t" << *crimen->obtenerCategory() << endl;
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
        unsigned int freq_ci = it->second ;

        info_gain = info_gain +
        (((double)freq_ci/(double)this->cantidad()) *
        log2((double)freq_ci/(double)this->cantidad()));

    }

    info_gain = info_gain * (-1.0);


    return info_gain;
}

DataFrame* DataFrame::filtrar(std::string nombre_atributo, std::string comparador, std::string condicion) {

    std::vector<Crimen*>* crimenes_filtrados = new std::vector<Crimen*>();

    int c = 0  ;


    for(std::vector<int>::size_type i = 0; i < this->crimenes->size(); i++) {

        Crimen* actual = (this->crimenes->at(i));

        if(this->cumpleCondicion(actual, nombre_atributo, comparador, condicion)) {
            crimenes_filtrados->push_back(actual);
        }

        c++;

        if( c % 50000 == 0) {
            cout << "Filtrados " << c << " crimenes." << endl;
        }
    }

    DataFrame* nueva_df = new DataFrame(crimenes_filtrados);

    return nueva_df;


}

bool DataFrame::cumpleCondicion(Crimen* actual, std::string nombre_atributo,
                            std::string comparador, std::string condicion) {

    if(nombre_atributo.compare("x") == 0 ) {

        double condicion_double = std::stod(condicion);

        if(comparador.compare("<") == 0) {
            if(actual->obtenerX() < condicion_double) {
                return true;
            }
        } else if(comparador.compare(">") == 0) {
            if(actual->obtenerX() > condicion_double) {
                return true;
            }
        }

    } else if(nombre_atributo.compare("y") == 0) {

        double condicion_double = std::stod(condicion);

        if(comparador.compare("<") == 0) {
            if(actual->obtenerY() < condicion_double) {
                return true;
            }
        } else if(comparador.compare(">") == 0) {
            if(actual->obtenerY() > condicion_double) {
                return true;
            }
        }


    } else if(nombre_atributo.compare("pdDistrict") == 0) {
        // comparador es irrelevante acá
        std::string pd_actual = *actual->obtenerPd();

        if(condicion.compare(pd_actual) == 0) {
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
}
