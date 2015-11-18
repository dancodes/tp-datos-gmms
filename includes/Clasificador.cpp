#include "Clasificador.hpp"
#include "DataFrame.hpp"
#include "TuplasCat.hpp"
#include <iostream>

void Clasificador::entrenar(DataFrame* entrenamientos) {
    std::cout << "[TODO] Entrenando clasificador..." << std::endl;
}

DataFrame* Clasificador::predecir(DataFrame* entrenamientos) {
    std::cout << "[TODO] Prediciendo crimenes..." << std::endl;
    DataFrame* dtf = new DataFrame;
    return dtf;
}

double Clasificador::calculoInfoGainDP(DataFrame* entrenamientos){
    std::map<string, TuplasCat*> frequencia_de_clase = std::map<string, TuplasCat*>();

    for(int i = 0; i < entrenamientos->cantidad(); i++) {

        Crimen* actual = entrenamientos->at(i);
        std::string atributo_actual = *actual->obtenerPd();
        std::string categoria_actual = *actual->obtenerCategory();

        if(frequencia_de_clase.count(atributo_actual) == 0) {
            TuplasCat* vectorTuplas = new TuplasCat();
            frequencia_de_clase[atributo_actual] = vectorTuplas;
            frequencia_de_clase[atributo_actual]->aumentarCat(categoria_actual);

        } else {
            frequencia_de_clase[atributo_actual]->aumentarCat(categoria_actual);
        }
    }
    double infoGain = 0;
    // show content:
    for (std::map<string, TuplasCat*>::iterator it=frequencia_de_clase.begin(); it!=frequencia_de_clase.end(); ++it) {
        infoGain = infoGain + (it->second->informationGain() *
                    (it->second->obtenerTotal() / (double)entrenamientos->cantidad()));
    }
    return infoGain * (-1.0);
}
