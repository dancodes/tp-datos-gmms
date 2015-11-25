#include "DataFrame.hpp"
#include "TuplasCat.hpp"
#include <string>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>
#include "Nodo.hpp"
#include "InfoEntropia.hpp"
#include "ResultadoEntropia.hpp"
#include "CriterioNodo.hpp"
#include "Categoria.hpp"


class Arbol {
    private:
        Nodo* inicio;
        string primero;
        DataFrame* setAEntrenar;
        int limitador;

        double calculoInfoGainSegunIntervalo(DataFrame* entrenamiento, std::string nombre_atributo, double comparador);
        ResultadoEntropia calculoInfoTotal(DataFrame* entrenamiento, char &maxCat);
        bool seguir(int contador, string cat);
        std::vector<Nodo*> split(Nodo* padre);
        ResultadoEntropia calcularMejorAtributo(InfoEntropia* info_entropia,int profundidad);
        char recorrerArbol(Nodo* hijo,Crimen* crimen);

    public:
        Arbol(DataFrame* entrenamiento);
        Arbol(DataFrame* entrenamiento,int limitador);
        void crecer();
        InfoEntropia* calcularEntropias(DataFrame* entrenamiento);
        ResultadoEntropia calculoInfoGainOptimoDeNumerico(DataFrame* entrenamiento, std::string nombre_atributo);
        ResultadoEntropia calculoInfoGainCategorico(DataFrame* entrenamiento, std::string nombre_atributo);
        char predecir(Crimen* crimen);
        void guardarEnDisco();
        ~Arbol();
};
