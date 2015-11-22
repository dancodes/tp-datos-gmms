#include <iostream>
#include <string>
#include "CriterioNodo.hpp"

class InfoEntropia {
public:
    double intervaloX;
    double intervaloY;
    double iGTot;
    double iGDP;
    double iGX;
    double iGY;
    std::string mayorCrimen;
    void resumen() {
        std::cout << std::endl;
        std::cout << "[RESUMEN DE INFOGAIN]" << std::endl;
        std::cout << "InfoGain total: \t" << this->iGTot << std::endl;
        std::cout << "InfoGain PD: \t\t" << this->iGDP << std::endl;
        std::cout << "InfoGain X: \t\t" << this->iGX << std::endl;
        std::cout << "InfoGain Y: \t\t" << this->iGY << std::endl;
        std::cout << std::endl;
    }
    CriterioNodo obtenerCriterio() {

        double iGX = this->iGTot - this->iGX;
        double iGY = this->iGTot - this->iGY;
        double iGDP = this->iGTot - this->iGDP;

        std::string categoria;
        std::string comparador;
        std::string condicion;

        if ((iGDP>iGX) && (iGDP>iGY)){
            categoria = "pdDistrict";
            comparador = "=";
            this->infoGain = iGDP;
            this->intervalo = 0;
        } else if ((iGX>iGY) && (iGX > iGDP)){
            this->categoria = "x";
            this->infoGain = iGX;
            this->intervalo = this->intervaloX;
        } else if ((iGY>iGX) && (iGY > iGDP)){
            this->categoria = "y";
            this->infoGain = iGY;
            this->intervalo = this->intervaloY;
        } else {
            this->categoria = "cat";
            this->atributo = this->mayorCrimen;
        }
    }
};
