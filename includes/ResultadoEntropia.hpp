#include <iostream>
#include <string>

class ResultadoEntropia {
public:
    ResultadoEntropia(std::string nombre_atributo, double entropia, double intervalo) {
        this->nombre_atributo = nombre_atributo;
        this->entropia = entropia;
        this->intervalo = intervalo;
    }

    std::string obtenerNombreAtributo() {
        return this->nombre_atributo;
    }

    double obtenerEntropia() {
        return this->entropia;
    }
    double obtenerIntervalo() {
        return this->intervalo;
    }
private:
    double entropia;
    double intervalo;
    std::string nombre_atributo;
};
