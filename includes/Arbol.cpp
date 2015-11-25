#include "Arbol.hpp"
#include <iostream>


extern unsigned long long int misses;

Arbol::Arbol(DataFrame* entrenamiento, int limitador) {
    std::string atribIncial("raiz");
    this->limitador =limitador;
    CriterioNodo criterio_vacio;
    this->inicio = new Nodo(entrenamiento, criterio_vacio, 0);

    unsigned int contador = 0;
    //std::cout << "Creando un arbol que aprende de " << entrenamiento->cantidad() << " crimenes" << std::endl;

    this->crecer();
}

Arbol::Arbol(DataFrame* entrenamiento) {
    std::string atribIncial("raiz");
    this->limitador =-1;
    CriterioNodo criterio_vacio;
    this->inicio = new Nodo(entrenamiento, criterio_vacio, 0);

    unsigned int contador = 0;
    //std::cout << "Creando un arbol que aprende de " << entrenamiento->cantidad() << " crimenes" << std::endl;

    this->crecer();
}

void Arbol::guardarEnDisco() {  //guarda una linea de resultados y el encabezado, flata hacerlo para mas lineas

    ofstream myfile;
    myfile.open ("resultados/arbol_generado.txt");

    myfile << std::endl << std::endl << "[ARBOL FINAL]" << std::endl << std::endl;

    std::stack<Nodo*> nodos;

    std::map<int, int> profundidades;

    Nodo* nodo_padre = this->inicio;
    nodos.push(nodo_padre);

    do {
        Nodo* nodo = nodos.top();
        nodos.pop();

        int profundidad = nodo->obtenerProfundidad();

        if(profundidad > 0) {
            myfile << std::string(profundidad*4 - 4, ' ') << "if " << nodo->obtenerCriterio().descripcion() << ":" << std::endl;
        }

        std::vector<Nodo*> hijos = *(nodo->obtenerHijos());

        for (int i=0; i<hijos.size(); i++) {
            Nodo* nodo = hijos[i];

            nodos.push(nodo);
        }

        if (nodo->esHoja()) {
            myfile << std::string(profundidad*4 + 4 - 4, ' ') << "return " << Categoria::obtenerNombre(nodo->obtenerCategoria()) << std::endl;

            if(profundidades.count(profundidad) == 0) {
                profundidades[profundidad] = 1;
            } else {
                profundidades[profundidad] = profundidades[profundidad] + 1;
            }

        }

    } while(nodos.size() > 0);

    for (std::map<int, int>::iterator it=profundidades.begin(); it!=profundidades.end(); ++it) {
        std::cout << "Profundidad " << it->first << ": " << it->second << std::endl;
    }

}

char Arbol::predecir(Crimen* crimen){
    return recorrerArbol(inicio,crimen);
}

char Arbol::recorrerArbol(Nodo* nodo, Crimen* crimen){
    Nodo* hijo;
    CriterioNodo criterio;
    //std::cout<<"recursivo"<<std::endl;
    if(nodo->esHoja()){
        //std::cout<<"hoja"<<std::endl;

        return nodo->obtenerCategoria();
    } else {
        std::vector<Nodo*>* hijos = nodo->obtenerHijos();

        for (unsigned int i=0; i< hijos->size(); i++) {
            Nodo* hijo = hijos->at(i);
            CriterioNodo criterio = hijo->obtenerCriterio();

            if(hijo->obtenerDataFrame()->cumpleCondicion(crimen, criterio)) {
                return recorrerArbol(hijo, crimen);
            }
        }
        misses++;
        return (char)(-1); // <-- nunca deberiamos llegar aca
    }
    /*} else if(nodo->obtenerHijos()->at(0)->obtenerCriterio().obtenerAtributo() == "pdDistrict"){
        //std::cout<<"pd"<<std::endl;
        criterio = nodo->obtenerHijos()->at(0)->obtenerCriterio();
        for(unsigned int i=0; i< nodo->obtenerHijos()->size(); i++){
            if (nodo->obtenerHijos()->at(i)->obtenerCriterio().obtenerCondicion()
                                == (*(crimen->obtenerPd()))){
                hijo= nodo->obtenerHijos()->at(i);
            }
        }
    }else{
        criterio = nodo->obtenerHijos()->at(0)->obtenerCriterio();
        //std::cout<<"x"<<std::endl;
        char c;
        if(criterio.obtenerAtributo() == "x"){
            c='x';
        }else{
            c='y';
        }

       if(crimen->obtenerNumerico(c)<=stod(criterio.obtenerCondicion())){
            hijo= nodo->obtenerHijos()->at(0);
            //std::cout<<"array pos0"<<std::endl;
       }else{
            //std::cout<<"array pos1"<<std::endl;
            hijo= nodo->obtenerHijos()->at(1);
       }
    }
    return recorrerArbol(hijo,crimen);*/
}

void Arbol::crecer() {
    std::queue<Nodo*> cola_de_nodos;
    cola_de_nodos.push(this->inicio);

    int nodos_agregados = 0;
    int punteros_borrados = 0;
    do {
        Nodo* nodo_actual = cola_de_nodos.front(); //Consigue el siguiente elemento de la cola
        cola_de_nodos.pop(); //Borra dicho elemento de la cola

        std::vector<Nodo*> nodos_creados = this->split(nodo_actual);


        for(int i = 0; i < nodos_creados.size(); i++) {
            Nodo* nodo_a_agregar = nodos_creados.at(i);
            cola_de_nodos.push(nodo_a_agregar);
        }

        if(nodos_agregados > 0) {
            //std::cout << "Borrado un DataFrame con " << nodo_actual->obtenerDataFrame()->cantidad() << " punteros" << std::endl;

            punteros_borrados = punteros_borrados + nodo_actual->obtenerDataFrame()->cantidad();

            nodo_actual->borrarDataFrame();
        }

        nodos_agregados++;

    } while(cola_de_nodos.size() > 0);

}

InfoEntropia* Arbol::calcularEntropias(DataFrame* entrenamiento) {

    InfoEntropia* info_ent = new InfoEntropia();

    ResultadoEntropia entropia_total = this->calculoInfoTotal(entrenamiento, info_ent->mayorCrimen);
    info_ent->iGTot = entropia_total.obtenerEntropia();

    ResultadoEntropia entropia_pd = this->calculoInfoGainCategorico(entrenamiento, "pdDistrict");
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

    ResultadoEntropia mejor_atributo = this->calcularMejorAtributo(info_entropia, nodo_original->obtenerProfundidad());

    if(mejor_atributo.obtenerEntropia() < 0.0 ||
       nodo_original->obtenerProfundidad() > 18) {
        //Acá sabemos que el nodo va a ser una hoja - el final de una rama
        //anotamos su prediccion y terminamos.
        //std::cout << "[~~] Split termina con categoria " << mejor_atributo.obtenerNombreAtributo() << std::endl;

        nodo_original->establecerCategoria(
            mejor_atributo.obtenerMayorCrimen()
        );

        return nodos_creados;


    } else {

        int profundidad_nueva = nodo_original->obtenerProfundidad() + 1;

        if(mejor_atributo.obtenerNombreAtributo() == district) {
            std::vector<std::string>* posibles_opciones = nodo_original->obtenerDataFrame()
                                                          ->obtenerPosiblesOpciones("pdDistrict");

            for (int i=0; i<posibles_opciones->size(); i++) {
                std::string opcion_actual = posibles_opciones->at(i);
                CriterioNodo nuevo_criterio(mejor_atributo.obtenerNombreAtributo(),
                                            "=", opcion_actual);

                DataFrame* nuevo_df = nodo_original->obtenerDataFrame()->filtrar(nuevo_criterio);

                Nodo* hijo = new Nodo(nuevo_df, nuevo_criterio, profundidad_nueva);
                nodo_original->agregarNodo(hijo);
                nodos_creados.push_back(hijo);

                //std::cout << "[~~] Creado split con " << nuevo_criterio.descripcion() << std::endl;
            }

            delete posibles_opciones;
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

            //std::cout << "[~~] Creado split con " << nuevo_criterio_menor.descripcion() << " y " << nuevo_df_menor->cantidad() << " elementos" << std::endl;
            //std::cout << "[~~] Creado split con " << nuevo_criterio_mayor.descripcion() << " y " << nuevo_df_mayor->cantidad() << " elementos" << std::endl;

        }

        return nodos_creados;
    }
}

ResultadoEntropia Arbol::calcularMejorAtributo(InfoEntropia* info_entropia, int profundidad) {
    double iGX = info_entropia->iGTot - info_entropia->iGX;
    double iGY = info_entropia->iGTot - info_entropia->iGY;
    double iGDP = info_entropia->iGTot - info_entropia->iGDP;

    std::string nombre_atributo;
    double intervalo;
    double entropia;

    if ((iGX == iGY && iGY == iGDP && iGDP == 0.0)|| (this->limitador!= -1 && this->limitador >= profundidad)) {
        nombre_atributo = "";
        entropia = -1.0;
        intervalo = 0;
    } else if ((iGDP >= iGX) && (iGDP >= iGY)) {
        nombre_atributo = "pdDistrict";
        entropia = iGDP;
        intervalo = 0;
    } else if ((iGX >= iGY) && (iGX >= iGDP)) {
        nombre_atributo = "x";
        entropia = iGX;
        intervalo = info_entropia->intervaloX;
    } else if ((iGY >= iGX) && (iGY >= iGDP))  {
        nombre_atributo = "y";
        entropia = iGY;
        intervalo = info_entropia->intervaloY;
    }

    //std::cout << "atrib " << nombre_atributo << " ent " << entropia << " int " << intervalo << std::endl;

    ResultadoEntropia resultado(nombre_atributo, entropia, intervalo, info_entropia->mayorCrimen);

    delete info_entropia;

    return resultado;

}

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

    int secciones = 3;
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

    for (int i=1; i<secciones; i++) {
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

    std::map<char, TuplasCat*> frequencia_de_clase = std::map<char, TuplasCat*>();



    for(std::vector<int>::size_type i = 0; i < entrenamiento->cantidad(); i++) {
        Crimen* actual = entrenamiento->at(i);

        // Valor del atributo casteado a Double
        double valor_atributo = *(double*)actual->obtenerAtributo(nombre_atributo);

        //si es menor o igual al comparador lo agrupo con los menores, sino con los mayores
        char menor_o_mayor;

        if(valor_atributo <= comparador) {
            menor_o_mayor = 'm'; //menores
        } else {
            menor_o_mayor = 'M'; //mayores
        }

        char categoria_actual = actual->obtenerCategory();
        if(frequencia_de_clase.count(menor_o_mayor) == 0) {
            TuplasCat* vectorTuplas= new TuplasCat();
            frequencia_de_clase[menor_o_mayor] = vectorTuplas;
            frequencia_de_clase[menor_o_mayor]->aumentarPosicion(categoria_actual);
        } else {
                frequencia_de_clase[menor_o_mayor]->aumentarPosicion(categoria_actual);
        }
    }
    double infoGain = 0;
    // show content:
    for (std::map<char, TuplasCat*>::iterator it=frequencia_de_clase.begin(); it!=frequencia_de_clase.end(); ++it) {
        infoGain = infoGain + (it->second->informationGain() *
                    (it->second->obtenerTotal() / (double)entrenamiento->cantidad()));

        delete it->second;
    }
    return infoGain * (-1.0);
}

ResultadoEntropia Arbol::calculoInfoGainCategorico(DataFrame* entrenamiento, std::string nombre_atributo) {

    struct cmp_str
    {
       bool operator()(char const *a, char const *b) const
       {
          return std::strcmp(a, b) < 0;
       }
    };


    std::map<char const*, TuplasCat*, cmp_str> frequencia_de_clase = std::map<char const*, TuplasCat*, cmp_str>();

    for(unsigned int i = 0; i < entrenamiento->cantidad(); i++) {
        Crimen* actual = entrenamiento->at(i);
        const char* atributo_actual = ((std::string*)actual->obtenerAtributo(nombre_atributo))->c_str();

        char categoria_actual = actual->obtenerCategory();

        if(frequencia_de_clase.count(atributo_actual) == 0) {
            TuplasCat* vectorTuplas = new TuplasCat();
            frequencia_de_clase[atributo_actual] = vectorTuplas;
            frequencia_de_clase[atributo_actual]->aumentarPosicion(categoria_actual);

        } else {
            frequencia_de_clase[atributo_actual]->aumentarPosicion(categoria_actual);
        }
    }
    double infoGain = 0;
    // show content:
    for (std::map<char const*, TuplasCat*, cmp_str>::iterator it=frequencia_de_clase.begin(); it!=frequencia_de_clase.end(); ++it) {
        infoGain = infoGain + (it->second->informationGain() *
                    (it->second->obtenerTotal() / (double)entrenamiento->cantidad()));

        delete it->second;
    }

    ResultadoEntropia resultado(nombre_atributo, infoGain * (-1.0), 0.0);

    return resultado;
}


ResultadoEntropia Arbol::calculoInfoTotal(DataFrame* entrenamiento, char &mayorCrimen) { //por Mati

    TuplasCat* vectorTuplas = new TuplasCat();
    for(unsigned int i = 0; i < entrenamiento->cantidad(); i++) {

        Crimen* actual = entrenamiento->at(i);

        char categoria_actual = actual->obtenerCategory();
        vectorTuplas->aumentarPosicion(categoria_actual);
    }

    mayorCrimen = vectorTuplas->mayorCrimen();
    double infoGain = (vectorTuplas->informationGain());

    ResultadoEntropia resultado("Total", infoGain * (-1.0), 0.0);

    delete vectorTuplas;

    return resultado;
}

Arbol::~Arbol() {
    delete this->inicio;
}
