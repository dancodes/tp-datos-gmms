#include "Clasificador.hpp"
#include "DataFrame.hpp"
#include "TuplasCat.hpp"
#include <iostream>

void Clasificador::entrenar(DataFrame* entrenamientos) {
    std::cout << "[TODO] Entrenando clasificador..." << std::endl; //Nach0 es un poco mas Crudo que Dani
}


double Clasificador::calculoInfoGainXoY(DataFrame* entrenamientos) {
    double maxi = (entrenamientos->at(0))->obtenerX();
    double mini = (entrenamientos->at(0))->obtenerX();
    for (int i=1 ; i < entrenamientos->cantidad() ; i++){
        if (((entrenamientos->at(i)))->obtenerX() > maxi ){
            maxi = ((entrenamientos->at(i)))->obtenerX();
        }
        if ((entrenamientos->at(i))->obtenerX() < mini ){
            mini = (entrenamientos->at(i))->obtenerX();
        }
    }
    double intervalo = (maxi - mini)/10;
    double mayorGan = 0;
    double gananciaNum = 0;
    int indice= 0;
    for (int i= 1 ; i < 10 ; i++){
        gananciaNum = calculoInfoGainNumerico(entrenamientos, (mini+intervalo*i));
        if (mayorGan < gananciaNum) {
            mayorGan = gananciaNum;
            indice = i;
        }
    }
    return gananciaNum;
}

double Clasificador::calculoInfoGainNumerico(DataFrame* entrenamientos , double comparador) {
    std::map<string, TuplasCat*> frequencia_de_clase = std::map<string, TuplasCat*>();
    for(std::vector<int>::size_type i = 0; i < entrenamientos->cantidad(); i++) {
        Crimen* actual = entrenamientos->at(i);
            //si es menor o igual al comparador lo agrupo con los menores, sino con los mayores
        std::string atributo_actual;
            if(actual->obtenerX()<=comparador){
                atributo_actual = "menor";
            }else{
                atributo_actual = "mayor";
            }
        std::string categoria_actual = *actual->obtenerCategory();
        if(frequencia_de_clase.count(atributo_actual) == 0) {
            TuplasCat* vectorTuplas= new TuplasCat();
            frequencia_de_clase[atributo_actual] = vectorTuplas;
        } else {
                frequencia_de_clase[atributo_actual]->aumentarCat(categoria_actual);
        }
    }
    double infoGain = 0;
    // show content:
    for (std::map<string, TuplasCat*>::iterator it=frequencia_de_clase.begin(); it!=frequencia_de_clase.end(); ++it) {
        infoGain = infoGain + (it->second->informationGain() *
                    (it->second->obtenerTotal() / entrenamientos->cantidad()));
    }
    return infoGain;
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
