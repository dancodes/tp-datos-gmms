#pragma once

#include <iostream>
#include <string>
#include "DiccionarioCategorias.hpp"

class Categoria {
    ;
private:
    Categoria() {}

public:
    static DiccionarioCategorias dc_;
    static char obtenerIndice(std::string nombre) {

        char resultado = -1;

        for (int i=0; i < 39; i++) {
            if (dc_.diccionario[i] == nombre) {
                resultado = (char)i;
            }
        }

        return resultado;
    }
    static std::string obtenerNombre(char index) {
        return dc_.diccionario[index];
    }


};
