#include "Arbol.hpp"
#include <iostream>

#include "../configuracion.h"

#include "NAtributo.hpp"

extern unsigned long long int misses;

Arbol::Arbol(DataFrame* entrenamiento, int limitador, char algoritmo_de_impureza) {
    std::string atribIncial("raiz");
    this->limitador = limitador;
    this->algoritmo_de_impureza = algoritmo_de_impureza;
    CriterioNodo criterio_vacio;
    this->inicio = new Nodo(entrenamiento, criterio_vacio, 0);

    unsigned int contador = 0;
    //std::cout << "Creando un arbol que aprende de " << entrenamiento->cantidad() << " crimenes" << std::endl;

    this->crecer();
}

Arbol::Arbol(DataFrame* entrenamiento) {
    std::string atribIncial("raiz");
    this->limitador = 7;
    this->algoritmo_de_impureza = 'e';
    CriterioNodo criterio_vacio;
    this->inicio = new Nodo(entrenamiento, criterio_vacio, 0);

    unsigned int contador = 0;
    //std::cout << "Creando un arbol que aprende de " << entrenamiento->cantidad() << " crimenes" << std::endl;

    this->crecer();
}

TuplasCat* Arbol::predecir(Crimen* crimen){
    return recorrerArbol(inicio,crimen);
}

TuplasCat* Arbol::recorrerArbol(Nodo* nodo, Crimen* crimen){
    Nodo* hijo;
    CriterioNodo criterio;
    //std::cout<<"recursivo"<<std::endl;
    if(nodo->esHoja()){
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
        return NULL; // <-- nunca deberiamos llegar aca
    }
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

    Crimen* ejemplo = entrenamiento->at(0);

    std::map<std::string, NAtributo*>* atributos = ejemplo->obtenerAtributos();

    InfoEntropia* info_ent = new InfoEntropia();

    for (std::map<std::string, NAtributo*>::iterator it=atributos->begin(); it!=atributos->end(); ++it) {

        const std::string* nombre_atributo = &it->first;

        NAtributo* atributo = it->second;

        if(atributo->esNumerico()) {
            ResultadoEntropia entropia_num = this->calculoInfoGainOptimoDeNumerico(entrenamiento, *nombre_atributo);
            info_ent->entropias[*nombre_atributo] = entropia_num.obtenerEntropia();
            info_ent->intervalos[*nombre_atributo] = entropia_num.obtenerIntervalo();
        } else {

            ResultadoEntropia entropia_cat = this->calculoInfoGainCategorico(entrenamiento, *nombre_atributo);
            info_ent->entropias[*nombre_atributo] = entropia_cat.obtenerEntropia();
            info_ent->intervalos[*nombre_atributo] = 0.0;
        }
    }

    ResultadoEntropia entropia_total = this->calculoInfoTotal(entrenamiento, info_ent->mayorCrimen);
    info_ent->iGTot = entropia_total.obtenerEntropia();

    return info_ent;
}


ResultadoEntropia Arbol::calcularMejorAtributo(InfoEntropia* info_entropia, int profundidad) {


    std::string mejor_atributo_nombre;
    double mejor_atributo_infogain = 0.0;
    double mejor_atributo_intervalo = 0.0;

    std::map<std::string, double>* entropias = &info_entropia->entropias;
    std::map<std::string, double>* intervalos = &info_entropia->intervalos;

    for (std::map<std::string, double>::iterator it=entropias->begin(); it!=entropias->end(); ++it) {
        double entropia = it->second;
        double info_gain = info_entropia->iGTot - entropia;

        if(info_gain > mejor_atributo_infogain) {
            mejor_atributo_nombre = it->first;
            mejor_atributo_infogain = info_gain;
            mejor_atributo_intervalo = (*intervalos)[mejor_atributo_nombre];
        }
    }

    if(mejor_atributo_infogain == 0.0 || profundidad > this->limitador) {
        mejor_atributo_nombre = "";
        mejor_atributo_infogain = -1.0;
        mejor_atributo_intervalo = 0;
    }




    ResultadoEntropia resultado(mejor_atributo_nombre, mejor_atributo_infogain, mejor_atributo_intervalo, info_entropia->mayorCrimen);

    delete info_entropia;
    return resultado;

}


bool Arbol::seguir(int contador, string cat) {
    //falta agregarla la otra condicion de corte
    int piso = 1;
    return (contador<piso) && (cat != "cat");
}

std::vector<Nodo*> Arbol::split(Nodo* nodo_original) {

    std::vector<Nodo*> nodos_creados;

    DataFrame* df_original = nodo_original->obtenerDataFrame();

    InfoEntropia* info_entropia = this->calcularEntropias(df_original);

    ResultadoEntropia mejor_atributo = this->calcularMejorAtributo(info_entropia, nodo_original->obtenerProfundidad());


    if(mejor_atributo.obtenerEntropia() < 0.0) {
        //Acá sabemos que el nodo va a ser una hoja - el final de una rama
        //anotamos su prediccion y terminamos.
        //std::cout << "[~~] Split termina con categoria " << mejor_atributo.obtenerNombreAtributo() << std::endl;

        nodo_original->establecerCategoria(
            nodo_original->obtenerDataFrame()->generarProbabilidades()
        );

        return nodos_creados;


    } else {

        int profundidad_nueva = nodo_original->obtenerProfundidad() + 1;

        if(mejor_atributo.obtenerNombreAtributo() != "x" && mejor_atributo.obtenerNombreAtributo() != "y") {

            std::vector<std::string>* posibles_opciones = nodo_original->obtenerDataFrame()
                                                          ->obtenerPosiblesOpciones(
                                                              mejor_atributo.obtenerNombreAtributo()
                                                          );

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
        infoGain = infoGain + (it->second->informationGain(this->algoritmo_de_impureza) *
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
        infoGain = infoGain + (it->second->informationGain(this->algoritmo_de_impureza) *
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
    double infoGain = (vectorTuplas->informationGain(this->algoritmo_de_impureza));

    ResultadoEntropia resultado("Total", infoGain * (-1.0), 0.0);

    delete vectorTuplas;

    return resultado;
}

Arbol::~Arbol() {
    delete this->inicio;
}
