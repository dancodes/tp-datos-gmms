#include "DataFrame.hpp"

struct contenedor{
    double intervaloX;
    double intervaloY;
    double iGTot;
    double iGDP;
    double iGX;
    double iGY;
};

class Nodo
{
    public:
        Nodo();
        Nodo(DataFrame* df, contenedor contIg);
        void AgregarNodo(Nodo* nodoAAgregar);
        Nodo* ObtenerNodo();
        ~Nodo();
        contenedor cont;
    private:
        DataFrame* dataFrame;
        std::string atributo;
        std::string categoria;
        double intervalo;
        double infoGain;
        std::vector<Nodo*>* splits;
};

