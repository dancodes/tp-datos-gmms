#include "DataFrame.hpp"

class Nodo
{
    public:
        Nodo();
        Nodo(DataFrame* df,std::string atrib,std::string cat,double IG);
        void AgregarNodo(Nodo* nodoAAgregar);
        Nodo* ObtenerNodo();
        ~Nodo();
    private:
        DataFrame* dataFrame;
        std::string atributo;
        std::string categoria;
        double infoGain;
        std::vector<Nodo*>* splits;
};

