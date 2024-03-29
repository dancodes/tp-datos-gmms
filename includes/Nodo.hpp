#pragma once

#include "DataFrame.hpp"
#include <map>
#include "InfoEntropia.hpp"
#include "CriterioNodo.hpp"
#include <iostream>


class Nodo {
    public:
        Nodo();
        Nodo(DataFrame* df, CriterioNodo criterio, int profundidad);

        DataFrame* obtenerDataFrame();

        bool esHoja();
        void establecerCategoria(TuplasCat* cat);
        TuplasCat* obtenerCategoria();
        CriterioNodo obtenerCriterio();
        int obtenerProfundidad();
        void borrarDataFrame();

        std::string obtenerAtrib();
        void agregarNodo(Nodo* nodoAAgregar);
        Nodo* ObtenerNodo();
        double obtenerIntervalo();
        std::string obtenerCat();
        std::vector<Nodo*>* obtenerHijos();
        DataFrame* filtrarDFPD(std::string Cat,std::string atribHijos);
        DataFrame* filtrarDFNum(std::string Cat,std::string atribHijos,
                                                        std::string condicion);
        ~Nodo();

    private:

        // ----------- arriba de esto es todo feo

        DataFrame* dataFrame;
        std::vector<Nodo*>* splits;
        InfoEntropia* info_ig;
        CriterioNodo criterio;
        TuplasCat* categoria_final;
        int profundidad;
};
