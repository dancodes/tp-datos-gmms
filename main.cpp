#include <iostream>
#include <vector>

#include "includes/Menu.hpp"
#include "includes/DataFrame.hpp"
#include "includes/ContextoArchivos.hpp"
#include "includes/ClasificadorPorArboles.hpp"




using namespace std;


int main () {

    ContextoArchivos ctx;
    Menu menu;

    DataFrame df;

  //  std::vector<double> v= {10.5, 20.5, 30.5, 12.5, 50.5};
  //  df.guardarEnDisco(v);


    df.leerArchivoTrain();
    cout << "NORMAL" << endl;
    cout << "*****************************************************" << endl;
    df.resumen();

    //df.leerArchivoTest();
    //cout << "NORMAL" << endl;
    //cout << "*****************************************************" << endl;
    //df.resumen();
/*
    cout << "Filtrando SOLO SOUTHERN" << endl;
    cout << "*****************************************************" << endl;

    DataFrame* df_filt = df.filtrar("pdDistrict","=","SOUTHERN");
    df_filt->resumen();

    cout << "Filtrando CON MENOR A" << endl;
    cout << "*****************************************************" << endl;

    DataFrame* df_filt2 = df.filtrar("y","<","378008726327.692");
    df_filt2->resumen();

    cout << "Filtrando CON MENOR A Y NORTHERN" << endl;
    cout << "*****************************************************" << endl;

    DataFrame* df_filt3 = df_filt2->filtrar("pdDistrict","=","NORTHERN");
    df_filt3->resumen();
*/
    //Cargamos los datos especificados por el usuario en el contexto

    menu.cargarDatos(ctx);

    ClasificadorPorArboles clf;
    clf.entrenar(&df);

    //Aprende de los datos de train.csv
    //clf.entrenar(ctx.obtenerEntrenamiento());

    //Y hacemos una prediccion sobre los crimenes de test.csv
    DataFrame* resultados = clf.predecir(ctx.obtenerIncognitas());

    //Guardamos todo en el formato correcto para Kaggle
//    resultados->guardarEnDisco();


    return 0;

}
