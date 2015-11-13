#pragma once
#include "Crimen.hpp"
#include <vector>

using namespace std;



class DataFrame {
public:
    DataFrame();
    void guardarEnDisco();
    void leerArchivo();
    ~DataFrame();
private:
    std::vector<Crimen*> crimenes;
    
};
