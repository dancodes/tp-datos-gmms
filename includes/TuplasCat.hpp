
#define  CSV_IO_NO_THREAD


#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
using namespace std;

struct TuplaCat{
    string cat;
    int cant;
};

class TuplasCat{
private:
    int total;
public:
    TuplaCat vector[39];
    void aumentarCat(string cat){
        for (int i=0; i<39; i++){
            if (vector[i].cat == cat){
                vector[i].cant ++;
            }
        }
        total ++;
    }
    TuplasCat(){
        vector[0].cat = "WARRANTS";
        vector[1].cat = "OTHER OFFENSES";
        vector[2].cat = "LARCENY/THEFT";
        vector[3].cat = "VEHICLE THEFT";
        vector[4].cat = "VANDALISM";
        vector[5].cat = "NON-CRIMINAL";
        vector[6].cat = "ROBBERY";
        vector[7].cat = "ASSAULT";
        vector[8].cat = "WEAPON LAWS";
        vector[9].cat = "BURGLARY";
        vector[10].cat = "SUSPICIOUS OCC";
        vector[11].cat = "DRUNKENNESS";
        vector[12].cat = "FORGERY/COUNTERFEITING";
        vector[13].cat = "DRUG/NARCOTIC";
        vector[14].cat = "STOLEN PROPERTY";
        vector[15].cat = "SECONDARY CODES";
        vector[16].cat = "TRESPASS";
        vector[17].cat = "MISSING PERSON";
        vector[18].cat = "FRAUD";
        vector[19].cat = "KIDNAPPING";
        vector[20].cat = "RUNAWAY";
        vector[21].cat = "DRIVING UNDER THE INFLUENCE";
        vector[22].cat = "SEX OFFENSES FORCIBLE";
        vector[23].cat = "PROSTITUTION";
        vector[24].cat = "DISORDERLY CONDUCT";
        vector[25].cat = "ARSON";
        vector[26].cat = "FAMILY OFFENSES";
        vector[27].cat = "LIQUOR LAWS";
        vector[28].cat = "BRIBERY";
        vector[29].cat = "EMBEZZLEMENT";
        vector[30].cat = "SUICIDE";
        vector[31].cat = "LOITERING";
        vector[32].cat = "SEX OFFENSES NON FORCIBLE";
        vector[33].cat = "EXTORTION";
        vector[34].cat = "GAMBLING";
        vector[35].cat = "BAD CHECKS";
        vector[36].cat = "TREA";
        vector[37].cat = "RECOVERED VEHICLE";
        vector[38].cat = "PORNOGRAPHY/OBSCENE MAT";
        for (int i=0; i<39; i++){
            vector[i].cant = 0;
        }
        this->total = 0;
    }
    int obtenerTotal(){
        return total;
    }

    double entropia(){
        double valor= 0;
        for (int i= 0; i < 39 ; i++){
            valor = valor + ((vector[i].cant / total)* log2((vector[i].cant / total)));
        }
        return valor;
    }
};