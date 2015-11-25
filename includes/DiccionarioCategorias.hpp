#pragma once

#include <iostream>
#include <string>

class DiccionarioCategorias {
public:
    DiccionarioCategorias() {
        this->diccionario[0] = "ARSON";
        this->diccionario[1] = "ASSAULT";
        this->diccionario[2] = "BAD CHECKS";
        this->diccionario[3] = "BRIBERY";
        this->diccionario[4] = "BURGLARY";
        this->diccionario[5] = "DISORDERLY CONDUCT";
        this->diccionario[6] = "DRIVING UNDER THE INFLUENCE";
        this->diccionario[7] = "DRUG/NARCOTIC";
        this->diccionario[8] = "DRUNKENNESS";
        this->diccionario[9] = "EMBEZZLEMENT";
        this->diccionario[10] = "EXTORTION";
        this->diccionario[11] = "FAMILY OFFENSES";
        this->diccionario[12] = "FORGERY/COUNTERFEITING";
        this->diccionario[13] = "FRAUD";
        this->diccionario[14] = "GAMBLING";
        this->diccionario[15] = "KIDNAPPING";
        this->diccionario[16] = "LARCENY/THEFT";
        this->diccionario[17] = "LIQUOR LAWS";
        this->diccionario[18] = "LOITERING";
        this->diccionario[19] = "MISSING PERSON";
        this->diccionario[20] = "NON-CRIMINAL";
        this->diccionario[21] = "OTHER OFFENSES";
        this->diccionario[22] = "PORNOGRAPHY/OBSCENE MAT";
        this->diccionario[23] = "PROSTITUTION";
        this->diccionario[24] = "RECOVERED VEHICLE";
        this->diccionario[25] = "ROBBERY";
        this->diccionario[26] = "RUNAWAY";
        this->diccionario[27] = "SECONDARY CODES";
        this->diccionario[28] = "SEX OFFENSES FORCIBLE";
        this->diccionario[29] = "SEX OFFENSES NON FORCIBLE";
        this->diccionario[30] = "STOLEN PROPERTY";
        this->diccionario[31] = "SUICIDE";
        this->diccionario[32] = "SUSPICIOUS OCC";
        this->diccionario[33] = "TREA";
        this->diccionario[34] = "TRESPASS";
        this->diccionario[35] = "VANDALISM";
        this->diccionario[36] = "VEHICLE THEFT";
        this->diccionario[37] = "WARRANTS";
        this->diccionario[38] = "WEAPON LAWS";
    }

    std::string diccionario[39];

};
