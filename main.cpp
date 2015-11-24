#include <iostream>
#include <vector>

#include "includes/Menu.hpp"
#include "includes/DataFrame.hpp"
#include "includes/ContextoArchivos.hpp"
#include "includes/ClasificadorPorArboles.hpp"
#include "includes/TuplasCat.hpp"


unsigned long long int dataframes_creados = 0;
unsigned long long int nodos_creados = 0;

using namespace std;


int main () {

    ContextoArchivos ctx;
    Menu menu;

    DataFrame df;

    cout << "SIZEOF Nodo " << sizeof(Nodo) << endl;
    cout << "SIZEOF DataFrame " << sizeof(DataFrame) << endl;
    cout << "SIZEOF Crimen " << sizeof(Crimen) << endl;
    cout << "SIZEOF CriterioNodo " << sizeof(CriterioNodo) << endl;
    cout << "SIZEOF InfoEntropia " << sizeof(InfoEntropia) << endl;
    cout << "SIZEOF std::string " << sizeof(std::string) << endl;
    cout << "SIZEOF DataFrame* " << sizeof(DataFrame*) << endl;
    cout << "SIZEOF DataFrame " << sizeof(DataFrame) << endl;
    cout << "SIZEOF std::vector<Crimen*> " << sizeof(std::vector<Crimen*>) << endl;



    //return 0;

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


    std::vector<TuplasCat*>* resultados = clf.predecir(&df);

    std::cout << "DATAFRAMES CREADOS: " << dataframes_creados << std::endl;
    std::cout << "NODOS CREADOS: " << nodos_creados << std::endl;


    //Borramos las predicciones de la memoria cuando ya no las usemos
    for(int i = 0; i < resultados->size(); i++) {
        delete resultados->at(i);
    }

    delete resultados;

    //df.guardarEnDisco(resultados);


    //Aprende de los datos de train.csv
    //clf.entrenar(ctx.obtenerEntrenamiento());

    //Y hacemos una prediccion sobre los crimenes de test.csv
    //
    //std::vector<TuplasCat*>* resultados = clf.predecir(ctx.obtenerIncognitas());

    //Guardamos todo en el formato correcto para Kaggle
    //resultados->guardarEnDisco();


    return 0;

}
