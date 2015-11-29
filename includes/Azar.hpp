#pragma once

#include <random>

class Azar {
public:
    static int numeroAlAzar(unsigned int min, unsigned int max) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator
        std::uniform_int_distribution<> distr(min, max); // define the range

        return distr(eng);
    }

    static std::vector<int> numerosAlAzar(unsigned int min, unsigned int max, unsigned int cantidad) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator
        std::uniform_int_distribution<> distr(min, max); // define the range

        std::vector<int> numeros;

        for(int i=0; i<cantidad; i++) {
            numeros.push_back(distr(eng));
        }

        return numeros;
    }
};
