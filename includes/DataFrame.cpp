#include "DataFrame.hpp"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

void DataFrame::guardarEnDisco() {
    std::cout << "Guardando resultados en disco!" << std::endl;
}


void DataFrame::leerArchivo() {

    std::cout << "Leyendo archivo" << std::endl;
    ifstream myReadFile;
    myReadFile.open("includes\\textfile.txt");
    char output[100];
    if (myReadFile.is_open()) {
        std::cout << "Abri Archivo" << std::endl;
        while (!myReadFile.eof()) {

            myReadFile >> output;
            cout<<output;
           }
        myReadFile.close();
        }
    else{

     std::cout << "Problemas al leer archivo" << std::endl;
     // abria q hacer q se cierre el programa
    }


}
