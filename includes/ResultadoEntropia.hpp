#include <iostream>
#include <string>

class ResultadoEntropia {
public:
    ResultadoEntropia(double entropia, double intervalo) {
        this->entropia = entropia;
        this->intervalo = intervalo;
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
};
