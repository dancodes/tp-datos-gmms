// constructing vectors
#include <iostream>
#include <vector>

#include "includes/Menu.hpp"
#include "includes/DataFrame.hpp"
#include "includes/ContextoArchivos.hpp"
#include "includes/Clasificador.hpp"

using namespace std;

int main () {

    ContextoArchivos ctx;
    Menu menu;
    DataFrame df;
    df.leerArchivo();

    //Cargamos los datos especificados por el usuario en el contexto

    menu.cargarDatos(ctx);

    Clasificador clf;

    //Aprende de los datos de train.csv
    clf.entrenar(ctx.obtenerEntrenamiento());

    //Y hacemos una prediccion sobre los crimenes de test.csv
    DataFrame* resultados = clf.predecir(ctx.obtenerIncognitas());

    //Guardamos todo en el formato correcto para Kaggle
    resultados->guardarEnDisco();


    return 0;

}
