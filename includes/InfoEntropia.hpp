#include <iostream>
#include <string>

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
        std::cout << "InfoGain total: \t" << this->iGTot << std::endl;
        std::cout << "InfoGain PD: \t\t" << this->iGDP << std::endl;
        std::cout << "InfoGain X: \t\t" << this->iGX << std::endl;
        std::cout << "InfoGain Y: \t\t" << this->iGY << std::endl;
        std::cout << std::endl;
    }
};
