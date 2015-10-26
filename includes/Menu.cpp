#include "Menu.hpp"
#include "ContextoArchivos.hpp"

#include <iostream>

Menu::Menu() {

    const char* text =
    "#####################################################################\n"
    "#             SUPER FABULOSO CLASIFICADOR PARA 7506 DATOS           #\n"
    "#                        HECHO POR TEAM GMMS                        #\n"
    "#####################################################################\n";

    std::cout << text << std::endl;

    /*
    // constructors used in the same order as described above:
    vector<int> second (4e2,100);

    int age;
    cin >> age;*/
}

void Menu::cargarDatos(ContextoArchivos ctx) {
    std::cout << "Cargando datos..." << std::endl;
}
