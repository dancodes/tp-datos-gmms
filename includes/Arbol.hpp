#include "DataFrame.hpp"
#include "TuplasCat.hpp"
#include <string>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
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
        char algoritmo_de_impureza;
        std::vector<int> atributos_elegidos;

        double calculoInfoGainSegunIntervalo(DataFrame* entrenamiento, std::string nombre_atributo, double comparador);
        ResultadoEntropia calculoInfoTotal(DataFrame* entrenamiento, char &maxCat);
        bool seguir(int contador, string cat);
        std::vector<Nodo*> split(Nodo* padre);
        ResultadoEntropia calcularMejorAtributo(InfoEntropia* info_entropia,int profundidad);
        TuplasCat* recorrerArbol(Nodo* hijo,Crimen* crimen);

    public:
        Arbol(DataFrame* entrenamiento, int limitador, char algoritmo_de_impureza, bool atributos_al_azar);
        std::vector<int> elegirAtributos(DataFrame* entrenamiento, bool atributos_al_azar);
        void crecer();
        InfoEntropia* calcularEntropias(DataFrame* entrenamiento);
        ResultadoEntropia calculoInfoGainOptimoDeNumerico(DataFrame* entrenamiento, std::string nombre_atributo);
        ResultadoEntropia calculoInfoGainCategorico(DataFrame* entrenamiento, std::string nombre_atributo);
        TuplasCat* predecir(Crimen* crimen);
        //void guardarEnDisco();
        ~Arbol();
};
