#include "DataFrame.hpp"

class Nodo
{
    public:
        Nodo();
        void AgregarNodo(Nodo* nodoAAgregar);
        Nodo* ObtenerNodo();
        ~Nodo();
    private:
        //hay q ver el tipo de datos de la condicion
        //ejemplo, si guardamos el numero por el cual vemos si es mayor o menor
        // guardar ese num, y en otro caso guardar el atributo con el cual spliteamos..
        double infoGain;
        std::vector<Nodo*>* splits;
};

