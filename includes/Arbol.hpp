#include "DataFrame.hpp"
#include "TuplasCat.hpp"
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include "Nodo.hpp"
#include "InfoEntropia.hpp"
#include "ResultadoEntropia.hpp"
#include "CriterioNodo.hpp"


class Arbol {
    private:
        Nodo* inicio;
        string primero;
        DataFrame* setAEntrenar;

        double calculoInfoGainSegunIntervalo(DataFrame* entrenamiento, std::string nombre_atributo, double comparador);
        ResultadoEntropia calculoInfoTotal(DataFrame* entrenamiento, string &maxCat);
        bool seguir(int contador, string cat);
        std::vector<Nodo*> split(Nodo* padre);
        ResultadoEntropia calcularMejorAtributo(InfoEntropia* info_entropia);
        std::string RecorrerArbol(Nodo* hijo,Crimen* crimen);

    public:
        Arbol(DataFrame* entrenamiento);
        void crecer();
        InfoEntropia* calcularEntropias(DataFrame* entrenamiento);
        ResultadoEntropia calculoInfoGainOptimoDeNumerico(DataFrame* entrenamiento, std::string nombre_atributo);
        ResultadoEntropia calculoInfoGainCategorico(DataFrame* entrenamiento, std::string nombre_atributo);
        std::string Predecir(Crimen* crimen);
        void guardarEnDisco();
        ~Arbol();
};
