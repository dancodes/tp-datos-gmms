#include "Arbol.hpp"
#include <iostream>




Arbol::Arbol(DataFrame* entrenamiento) {
    std::string atribIncial("raiz");

    CriterioNodo criterio_vacio;
    this->inicio = new Nodo(entrenamiento, criterio_vacio, 0);

    unsigned int contador = 0;
    std::cout << "PRIMER SPLIT DEL ARBOL" << std::endl;

    this->crecer();
}

void Arbol::guardarEnDisco() {  //guarda una linea de resultados y el encabezado, flata hacerlo para mas lineas

    ofstream myfile;
    myfile.open ("resultados/arbol_generado.txt");

    myfile << std::endl << std::endl << "[ARBOL FINAL]" << std::endl << std::endl;

    std::stack<Nodo*> nodos;

    Nodo* nodo_padre = this->inicio;
    nodos.push(nodo_padre);

    do {
        Nodo* nodo = nodos.top();
        nodos.pop();

        if(nodo->obtenerProfundidad() > 0) {
            myfile << std::string(nodo->obtenerProfundidad()*4 - 4, ' ') << "if " << nodo->obtenerCriterio().descripcion() << ":" << std::endl;
        }

        std::vector<Nodo*> hijos = *(nodo->obtenerHijos());

        for (int i=0 ; i<hijos.size();i++) {
            Nodo* nodo = hijos[i];

            nodos.push(nodo);
        }

        if (nodo->esHoja()) {
            myfile << std::string(nodo->obtenerProfundidad()*4 + 4 - 4, ' ') << "return " << nodo->obtenerCategoria() << std::endl;
        }

    } while(nodos.size() > 0);

    myfile.close();
}

void Arbol::crecer() {
    std::queue<Nodo*> cola_de_nodos;
    cola_de_nodos.push(this->inicio);

    do {
        Nodo* nodo_actual = cola_de_nodos.front(); //Consigue el siguiente elemento de la cola
        cola_de_nodos.pop(); //Borra dicho elemento de la cola

        std::vector<Nodo*> nodos_creados = this->split(nodo_actual);

        for(int i = 0; i < nodos_creados.size(); i++) {
            Nodo* nodo_a_agregar = nodos_creados.at(i);
            cola_de_nodos.push(nodo_a_agregar);
        }

    } while(cola_de_nodos.size() > 0);
}

InfoEntropia* Arbol::calcularEntropias(DataFrame* entrenamiento) {
    InfoEntropia* info_ent = new InfoEntropia();

    ResultadoEntropia entropia_total = this->calculoInfoTotal(entrenamiento, info_ent->mayorCrimen);
    info_ent->iGTot = entropia_total.obtenerEntropia();

    ResultadoEntropia entropia_pd = this->calculoInfoGainCategorico(entrenamiento, "pd");
    info_ent->iGDP = entropia_pd.obtenerEntropia();

    ResultadoEntropia entropia_x = this->calculoInfoGainOptimoDeNumerico(entrenamiento,"x");
    info_ent->iGX = entropia_x.obtenerEntropia();
    info_ent->intervaloX = entropia_x.obtenerIntervalo();

    ResultadoEntropia entropia_y = this->calculoInfoGainOptimoDeNumerico(entrenamiento,"y");
    info_ent->iGY = entropia_y.obtenerEntropia();
    info_ent->intervaloY = entropia_y.obtenerIntervalo();

    return info_ent;
}

bool Arbol::seguir(int contador, string cat) {
    //falta agregarla la otra condicion de corte
    int piso = 1;
    return (contador<piso) && (cat != "cat");
}

std::vector<Nodo*> Arbol::split(Nodo* nodo_original) {
    std::string district("pdDistrict");



    std::vector<Nodo*> nodos_creados;

    DataFrame* df_original = nodo_original->obtenerDataFrame();

    InfoEntropia* info_entropia = this->calcularEntropias(df_original);
    //info_entropia->resumen();
    std::cout << "[!] flor: " << df_original->cantidad() << " elementos" << std::endl;

    ResultadoEntropia mejor_atributo = this->calcularMejorAtributo(info_entropia);

    if(mejor_atributo.obtenerEntropia() < 0.0) {
        //Acá sabemos que el nodo va a ser una hoja - el final de una rama
        //anotamos su prediccion y terminamos.
        nodo_original->establecerCategoria(mejor_atributo.obtenerNombreAtributo());
        std::cout << "[~~] Split termina con categoria " << mejor_atributo.obtenerNombreAtributo() << std::endl;
        return nodos_creados;


    } else {

        int profundidad_nueva = nodo_original->obtenerProfundidad() + 1;

        if(mejor_atributo.obtenerNombreAtributo() == district) {
            std::vector<std::string>* posibles_opciones = nodo_original->obtenerDataFrame()
                                                          ->obtenerPosiblesOpciones("pd");

            for (int i=0; i<posibles_opciones->size(); i++) {
                std::string opcion_actual = posibles_opciones->at(i);
                CriterioNodo nuevo_criterio(mejor_atributo.obtenerNombreAtributo(),
                                            "=", opcion_actual);

                DataFrame* nuevo_df = nodo_original->obtenerDataFrame()->filtrar(nuevo_criterio);

                Nodo* hijo = new Nodo(nuevo_df, nuevo_criterio, profundidad_nueva);
                nodo_original->agregarNodo(hijo);
                nodos_creados.push_back(hijo);

                std::cout << "[~~] Creado split con " << nuevo_criterio.descripcion() << std::endl;
            }
        } else {
            std::string nombre_mejor_atributo = mejor_atributo.obtenerNombreAtributo();
            double mejor_intervalo = mejor_atributo.obtenerIntervalo();
            std::string mejor_intervalo_str = std::to_string(mejor_intervalo);

            CriterioNodo nuevo_criterio_menor(nombre_mejor_atributo,
                                        "<=", mejor_intervalo_str);
            CriterioNodo nuevo_criterio_mayor(nombre_mejor_atributo,
                                        ">", mejor_intervalo_str);

            DataFrame* nuevo_df_menor = nodo_original->obtenerDataFrame()
                                        ->filtrar(nuevo_criterio_menor);
            DataFrame* nuevo_df_mayor = nodo_original->obtenerDataFrame()
                                        ->filtrar(nuevo_criterio_mayor);

            Nodo* hijo_menor = new Nodo(nuevo_df_menor, nuevo_criterio_menor, profundidad_nueva);
            Nodo* hijo_mayor = new Nodo(nuevo_df_mayor, nuevo_criterio_mayor, profundidad_nueva);

            nodo_original->agregarNodo(hijo_menor);
            nodo_original->agregarNodo(hijo_mayor);

            nodos_creados.push_back(hijo_menor);
            nodos_creados.push_back(hijo_mayor);

            std::cout << "[~~] Creado split con " << nuevo_criterio_menor.descripcion() << std::endl;
            std::cout << "[~~] Creado split con " << nuevo_criterio_mayor.descripcion() << std::endl;

        }

        return nodos_creados;
    }
}

ResultadoEntropia Arbol::calcularMejorAtributo(InfoEntropia* info_entropia) {
    double iGX = info_entropia->iGTot - info_entropia->iGX;
    double iGY = info_entropia->iGTot - info_entropia->iGY;
    double iGDP = info_entropia->iGTot - info_entropia->iGDP;

    std::string nombre_atributo;
    double intervalo;
    double entropia;



    if ((iGDP>iGX) && (iGDP>iGY)) {
        nombre_atributo = "pdDistrict";
        entropia = iGDP;
        intervalo = 0;
    } else if ((iGX>iGY) && (iGX > iGDP)) {
        nombre_atributo = "x";
        entropia = iGX;
        intervalo = info_entropia->intervaloX;
    } else if ((iGY>iGX) && (iGY > iGDP)) {
        nombre_atributo = "y";
        entropia = iGY;
        intervalo = info_entropia->intervaloY;
    } else {
        nombre_atributo = info_entropia->mayorCrimen;
        entropia = -1.0;
        intervalo = 0;
    }

    ResultadoEntropia resultado(nombre_atributo, entropia, intervalo);

    return resultado;

}
/*
void Arbol::split2(Nodo* nodo_original, unsigned int contador) {
    std::string district("pdDistrict");

    if (this->seguir(contador, nodo_original->obtenerAtrib())) {
        if(nodo_original->obtenerAtrib() == district) {
            std::vector<std::string>* atribHijos = nodo_original->obtenerPosiblesOpciones("pd");

            for (int i=0; i<atribHijos->size(); i++) {
                DataFrame* df = nodo_original->filtrarDFPD(district,atribHijos->at(i));

                InfoEntropia* contIG = this->calcularEntropias(df);

                Nodo* hijo = new Nodo(df,contIG,atribHijos->at(i));
                nodo_original->agregarNodo(hijo);

                contador = contador+1;
                std::cout << "Dividiendo con atributo " << nodo_original->obtenerAtrib() << "y pd " << atribHijos->at(i) << " y contador " << contador << std::endl;
                this->split(hijo, contador);
            }
        } else {

            double intervalo = nodo_original->obtenerIntervalo();
            std::string intervaloStr = std::to_string(intervalo);

            DataFrame* dfMayores = nodo_original->filtrarDFNum(nodo_original->obtenerAtrib(),intervaloStr,">");
            DataFrame* dfMenores = nodo_original->filtrarDFNum(nodo_original->obtenerAtrib(),intervaloStr,"<");

            InfoEntropia* contIGMayores = this->calcularEntropias(dfMayores);
            InfoEntropia* contIGMenores = this->calcularEntropias(dfMenores);

            Nodo* hijoMayores = new Nodo(dfMayores,contIGMayores,"mayor");
            Nodo* hijoMenores = new Nodo(dfMenores,contIGMenores,"menor");

            nodo_original->agregarNodo(hijoMayores);
            nodo_original->agregarNodo(hijoMenores);

            contador = contador+1;
            std::cout << "Dividiendo con numeros y contador " << contador << std::endl;

            this->split(hijoMayores, contador);
            this->split(hijoMenores, contador);
        }
    }
}
*/
ResultadoEntropia Arbol::calculoInfoGainOptimoDeNumerico(DataFrame* entrenamiento, std::string nombre_atributo) {

    if(entrenamiento->cantidad() < 1) {
        std::cout << "[!] DataFrame sin elementos en " << nombre_atributo << ". InfoGain = 0" << std::endl;
        ResultadoEntropia resultado(nombre_atributo,0.0, 0.0);
        return resultado;
    }

    Crimen* primer_crimen = entrenamiento->at(0);

    double primer_valor_atributo = *(double*)primer_crimen->obtenerAtributo(nombre_atributo);

    double maxi = primer_valor_atributo;
    double mini = primer_valor_atributo;

    for (unsigned int i=1 ; i <entrenamiento->cantidad(); i++) {

        Crimen* actual = entrenamiento->at(i);
        double valor_atributo = *(double*)actual->obtenerAtributo(nombre_atributo);

        if (valor_atributo >= maxi ) {
            maxi = valor_atributo;
        } else if (valor_atributo <= mini) {
            mini = valor_atributo;
        }
    }

    int secciones = 20;
    double rango = maxi - mini;
    double intervalo = rango/(double)secciones;

    /*std::cout << "[ATRIBUTO NUMERICO] " << nombre_atributo << ": ";
    std::cout << "Max: " << maxi << "\t  ///  ";
    std::cout << "Min: " << mini << "\t  ///  ";
    std::cout << "Intervalo: " << intervalo << std::endl;*/

    double gananciaNum = 0;

    int indice = 0;
    /*double menorGan = this->calculoInfoGainSegunIntervalo
                    (entrenamiento, nombre_atributo, (mini+intervalo*1));*/

    double menorGan = 999999.9;

    for (int i=1; i<20; i++) {
        gananciaNum = this->calculoInfoGainSegunIntervalo(entrenamiento, nombre_atributo, (mini+intervalo*i));

        //std::cout << "InfoGain candidato: \t\t" << gananciaNum << " con intervalo " << (mini+intervalo*i) <<  std::endl;

        if (gananciaNum < menorGan) {
            menorGan = gananciaNum;
            indice = i;
        }
    }

    intervalo = mini + intervalo*indice;

    ResultadoEntropia resultado(nombre_atributo, gananciaNum, intervalo);

    return resultado;
}

double Arbol::calculoInfoGainSegunIntervalo(DataFrame* entrenamiento, std::string nombre_atributo, double comparador) {

    std::map<string, TuplasCat*> frequencia_de_clase = std::map<string, TuplasCat*>();

    for(std::vector<int>::size_type i = 0; i < entrenamiento->cantidad(); i++) {
        Crimen* actual = entrenamiento->at(i);

        // Valor del atributo casteado a Double
        double valor_atributo = *(double*)actual->obtenerAtributo(nombre_atributo);

        //si es menor o igual al comparador lo agrupo con los menores, sino con los mayores
        std::string atributo_actual;

        if(valor_atributo <= comparador) {
            atributo_actual = "menor";
        } else {
            atributo_actual = "mayor";
        }

        std::string categoria_actual = *actual->obtenerCategory();
        if(frequencia_de_clase.count(atributo_actual) == 0) {
            TuplasCat* vectorTuplas= new TuplasCat();
            frequencia_de_clase[atributo_actual] = vectorTuplas;
            frequencia_de_clase[atributo_actual]->aumentarCat(categoria_actual);
        } else {
                frequencia_de_clase[atributo_actual]->aumentarCat(categoria_actual);
        }
    }
    double infoGain = 0;
    // show content:
    for (std::map<string, TuplasCat*>::iterator it=frequencia_de_clase.begin(); it!=frequencia_de_clase.end(); ++it) {
        infoGain = infoGain + (it->second->informationGain() *
                    (it->second->obtenerTotal() / (double)entrenamiento->cantidad()));
    }
    return infoGain * (-1.0);
}

ResultadoEntropia Arbol::calculoInfoGainCategorico(DataFrame* entrenamiento, std::string nombre_atributo) {
    std::map<string, TuplasCat*> frequencia_de_clase = std::map<string, TuplasCat*>();

    for(unsigned int i = 0; i < entrenamiento->cantidad(); i++) {
        Crimen* actual = entrenamiento->at(i);
        std::string atributo_actual = *(std::string*)actual->obtenerAtributo(nombre_atributo);

        std::string categoria_actual = *actual->obtenerCategory();

        if(frequencia_de_clase.count(atributo_actual) == 0) {
            TuplasCat* vectorTuplas = new TuplasCat();
            frequencia_de_clase[atributo_actual] = vectorTuplas;
            frequencia_de_clase[atributo_actual]->aumentarCat(categoria_actual);

        } else {
            frequencia_de_clase[atributo_actual]->aumentarCat(categoria_actual);
        }
    }
    double infoGain = 0;
    // show content:
    for (std::map<string, TuplasCat*>::iterator it=frequencia_de_clase.begin(); it!=frequencia_de_clase.end(); ++it) {
        infoGain = infoGain + (it->second->informationGain() *
                    (it->second->obtenerTotal() / (double)entrenamiento->cantidad()));
    }

    ResultadoEntropia resultado(nombre_atributo, infoGain * (-1.0), 0.0);

    return resultado;
}


ResultadoEntropia Arbol::calculoInfoTotal(DataFrame* entrenamiento, string &mayorCrimen) { //por Mati

    TuplasCat* vectorTuplas = new TuplasCat();
    for(unsigned int i = 0; i < entrenamiento->cantidad(); i++) {

        Crimen* actual = entrenamiento->at(i);

        std::string categoria_actual = *actual->obtenerCategory();
        vectorTuplas->aumentarCat(categoria_actual);
    }

    mayorCrimen = vectorTuplas->mayorCrimen();
    double infoGain = (vectorTuplas->informationGain());

    ResultadoEntropia resultado("Total", infoGain * (-1.0), 0.0);

    return resultado;
}
