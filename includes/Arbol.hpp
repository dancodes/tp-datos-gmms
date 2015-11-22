#include "DataFrame.hpp"
#include "TuplasCat.hpp"
#include <string>
#include "Nodo.hpp"
#include "InfoEntropia.hpp"
#include "ResultadoEntropia.hpp"


class Arbol {
    private:
        Nodo* inicio;
        string primero;
        DataFrame* setAEntrenar;
        double calculoInfoGainSegunIntervalo(DataFrame* entrenamiento, std::string nombre_atributo, double comparador);
        ResultadoEntropia calculoInfoTotal(DataFrame* entrenamiento, string &maxCat);
        bool seguir(int contador, string cat);
        void split(Nodo* padre, unsigned int contador);

    public:
        Arbol(DataFrame* entrenamiento);
        InfoEntropia* calcularEntropias(DataFrame* entrenamiento);
        ResultadoEntropia calculoInfoGainOptimoDeNumerico(DataFrame* entrenamiento, std::string nombre_atributo);
        ResultadoEntropia calculoInfoGainCategorico(DataFrame* entrenamiento, std::string nombre_atributo);
        void mostrar();
};
