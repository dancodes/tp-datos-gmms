#include "DataFrame.hpp"
#include "TuplasCat.hpp"
#include <string>
#include "Nodo.hpp"


class Arbol {
    private:
        Nodo* inicio;
        string primero;
        DataFrame* setAEntrenar;
        double calculoInfoGainNumerico(DataFrame* entrenamiento , double comparador);
        double calculoInfoTotal(DataFrame* entrenamiento);
    public:
        Arbol(DataFrame* entrenamiento);
        contenedor InicializarCont(DataFrame* entrenamiento);
        double calculoInfoGainXoY(DataFrame* entrenamientom, char c, double &d);
        double calculoInfoGainDP(DataFrame* entrenamiento);
};
