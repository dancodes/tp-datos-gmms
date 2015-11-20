#include "DataFrame.hpp"
#include <map>

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
        Nodo(DataFrame* df, contenedor contIg, std::string atrib);
        contenedor cont;
        void AgregarNodo(Nodo* nodoAAgregar);
        Nodo* ObtenerNodo();
        double obtenerIntervalo();
        std::string obtenerCat();
        std::vector<std::string>* obtenerListaAtrib();
        DataFrame* filtrarDFPD(std::string Cat,std::string atribHijos);
        DataFrame* filtrarDFNum(std::string Cat,std::string atribHijos,
                                                        std::string condicion);
        ~Nodo();
    private:
        void SetDatos();
        DataFrame* dataFrame;
        std::string atributo;
        std::string categoria;
        double intervalo;
        double infoGain;
        std::vector<Nodo*>* splits;

};

