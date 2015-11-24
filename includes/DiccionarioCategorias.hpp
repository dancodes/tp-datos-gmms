#pragma once

#include <iostream>
#include <string>

class DiccionarioCategorias {
public:
    DiccionarioCategorias() {
        this->diccionario[0] = "WARRANTS";
        this->diccionario[1] = "OTHER OFFENSES";
        this->diccionario[2] = "LARCENY/THEFT";
        this->diccionario[3] = "VEHICLE THEFT";
        this->diccionario[4] = "VANDALISM";
        this->diccionario[5] = "NON-CRIMINAL";
        this->diccionario[6] = "ROBBERY";
        this->diccionario[7] = "ASSAULT";
        this->diccionario[8] = "WEAPON LAWS";
        this->diccionario[9] = "BURGLARY";
        this->diccionario[10] = "SUSPICIOUS OCC";
        this->diccionario[11] = "DRUNKENNESS";
        this->diccionario[12] = "FORGERY/COUNTERFEITING";
        this->diccionario[13] = "DRUG/NARCOTIC";
        this->diccionario[14] = "STOLEN PROPERTY";
        this->diccionario[15] = "SECONDARY CODES";
        this->diccionario[16] = "TRESPASS";
        this->diccionario[17] = "MISSING PERSON";
        this->diccionario[18] = "FRAUD";
        this->diccionario[19] = "KIDNAPPING";
        this->diccionario[20] = "RUNAWAY";
        this->diccionario[21] = "DRIVING UNDER THE INFLUENCE";
        this->diccionario[22] = "SEX OFFENSES FORCIBLE";
        this->diccionario[23] = "PROSTITUTION";
        this->diccionario[24] = "DISORDERLY CONDUCT";
        this->diccionario[25] = "ARSON";
        this->diccionario[26] = "FAMILY OFFENSES";
        this->diccionario[27] = "LIQUOR LAWS";
        this->diccionario[28] = "BRIBERY";
        this->diccionario[29] = "EMBEZZLEMENT";
        this->diccionario[30] = "SUICIDE";
        this->diccionario[31] = "LOITERING";
        this->diccionario[32] = "SEX OFFENSES NON FORCIBLE";
        this->diccionario[33] = "EXTORTION";
        this->diccionario[34] = "GAMBLING";
        this->diccionario[35] = "BAD CHECKS";
        this->diccionario[36] = "TREA";
        this->diccionario[37] = "RECOVERED VEHICLE";
        this->diccionario[38] = "PORNOGRAPHY/OBSCENE MAT";
    }

    std::string diccionario[39];

};
