#pragma once
#include "Crimen.hpp"
#include <vector>

using namespace std;



class DataFrame {
public:
    DataFrame();
    DataFrame(std::vector<Crimen*>* crimenes_previos);
    void guardarEnDisco();
    void leerArchivo();
    unsigned int cantidad();
    double infoGainPd();
    ~DataFrame();
private:
    std::vector<Crimen*>* crimenes;
};
