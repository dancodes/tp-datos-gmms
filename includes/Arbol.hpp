#include "DataFrame.hpp"
#include "TuplasCat.hpp"
#include <string>
#include "Nodo.hpp"


class Arbol {
    private:
        Nodo* inicio;
        string primero;
        DataFrame* setAEntrenar;
        double calculoInfoGainSegunIntervalo(DataFrame* entrenamiento, std::string nombre_atributo, double comparador);
        double calculoInfoTotal(DataFrame* entrenamiento, string &maxCat);
        bool Seguir(int contador, string cat);
        void Split(Nodo* padre, unsigned int contador);
    public:
        Arbol(DataFrame* entrenamiento);
        contenedor inicializarCont(DataFrame* entrenamiento);
        double calculoInfoGainOptimoDeNumerico(DataFrame* entrenamiento, std::string nombre_atributo, double &intervalo);
        double calculoInfoGainCategorico(DataFrame* entrenamiento, std::string nombre_atributo);
};
