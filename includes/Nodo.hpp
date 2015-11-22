#include "DataFrame.hpp"
#include <map>

class InfoEntropia;

class Nodo
{
    public:
        Nodo();
        Nodo(DataFrame* df, InfoEntropia* contIg, std::string atrib);
        std::string obtenerAtrib();
        void agregarNodo(Nodo* nodoAAgregar);
        Nodo* ObtenerNodo();
        double obtenerIntervalo();
        std::string obtenerCat();
        std::vector<Nodo*>* obtenerHijos();
        std::vector<std::string>* obtenerPosiblesOpciones(std::string nombre_atributo);
        DataFrame* filtrarDFPD(std::string Cat,std::string atribHijos);
        DataFrame* filtrarDFNum(std::string Cat,std::string atribHijos,
                                                        std::string condicion);
        ~Nodo();

    private:
        void setDatos();
        DataFrame* dataFrame;
        std::string atributo;
        std::string categoria;
        double intervalo;
        double infoGain;
        std::vector<Nodo*>* splits;
        InfoEntropia* info_ig;

};
