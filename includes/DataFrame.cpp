#include "DataFrame.hpp"

#include <iostream>

#include <fstream>
#include <string>

using namespace std;

void DataFrame::guardarEnDisco() {
    std::cout << "Guardando resultados en disco!" << std::endl;
}


void DataFrame::leerArchivo() {
{
    std::cout << "Leyendo archivo" << std::endl;
    ifstream myReadFile;
    myReadFile.open("C:\\Users\\flor\\Documents\\GitHub\\tp-datos-gmms\\includes\\textfile.txt");
    char output[100];
    if (myReadFile.is_open()) {
        std::cout << "Abri Archivo" << std::endl;
        while (!myReadFile.eof()) {


            myReadFile >> output;
            cout<<output;


            }
        }
    myReadFile.close();

    }
}
