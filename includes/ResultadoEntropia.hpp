#include <iostream>
#include <string>

class ResultadoEntropia {
public:
    ResultadoEntropia(std::string nombre_atributo, double entropia, double intervalo, char mayor_crimen) {
        this->nombre_atributo = nombre_atributo;
        this->entropia = entropia;
        this->intervalo = intervalo;
        this->mayor_crimen = mayor_crimen;
    }

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

    char obtenerMayorCrimen() {
        return this->mayor_crimen;
    }
private:
    double entropia;
    double intervalo;
    std::string nombre_atributo;
    char mayor_crimen;
};
