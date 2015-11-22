#include "Arbol.hpp"
#include <iostream>
#include <queue>



Arbol::Arbol(DataFrame* entrenamiento){
    std::string atribIncial("raiz");
    InfoEntropia* contIG = this->inicializarCont(entrenamiento);
    contIG->resumen();
    inicio = new Nodo(entrenamiento, contIG, atribIncial);
    unsigned int contador = 0;
    std::cout << "PRIMER SPLIT DEL ARBOL" << std::endl;
    this->split(inicio, contador);
}

InfoEntropia* Arbol::inicializarCont(DataFrame* entrenamiento) {
    InfoEntropia* info_ent = new InfoEntropia();
    info_ent->iGTot = this->calculoInfoTotal(entrenamiento, info_ent->mayorCrimen);
    info_ent->iGDP = this->calculoInfoGainCategorico(entrenamiento, "pd");
    info_ent->iGX = this->calculoInfoGainOptimoDeNumerico(entrenamiento,std::string("x"),
                    info_ent->intervaloX);
    info_ent->iGY = this->calculoInfoGainOptimoDeNumerico(entrenamiento,std::string("y"),
                    info_ent->intervaloY);
    return info_ent;
}

void Arbol::mostrar() {
    std::queue<Nodo*> nodos;

    int nivel = 1;

    Nodo* nodo_padre = this->inicio;
    nodos.push(nodo_padre);

    do {
        Nodo* nodo = nodos.front();
        nodos.pop();

        std::cout << std::string(nivel, '-') << nodo->obtenerCat() << std::endl;

        std::vector<Nodo*> hijos = *(nodo->obtenerHijos());

        for (int i=0 ; i<hijos.size();i++){
            Nodo* nodo = hijos[i];

            nodos.push(nodo);
        }
        nivel = nivel + 1;
        if (nodo->obtenerCat()== "cat"){
            std::cout << std::string(nivel, '-') << nodo->obtenerAtrib() << std::endl;
        }
    } while(nodos.size() > 0);
}

bool Arbol::seguir(int contador, string cat){
    //falta agregarla la otra condicion de corte
    int piso = 1;
    return (contador<piso) && (cat != "cat");
}

void Arbol::split(Nodo* padre, unsigned int contador) {
    std::string district("pdDistrict");
    if (this->seguir(contador, padre->obtenerCat())) {

        if(padre->obtenerCat() == district) {
            std::vector<std::string>* atribHijos = padre->obtenerListaAtrib();
            for (int i=0; i<atribHijos->size(); i++){
                DataFrame* df = padre->filtrarDFPD(district,atribHijos->at(i));
                InfoEntropia* contIG = this->inicializarCont(df);
                Nodo* hijo = new Nodo(df,contIG,atribHijos->at(i));
                padre->agregarNodo(hijo);
                contador = contador+1;
                std::cout << "Dividiendo con atributo " << padre->obtenerCat() << " y contador " << contador << std::endl;
                this->split(hijo, contador);

            }
        } else {
            double intervalo = padre->obtenerIntervalo();
            std::string intervaloStr = std::to_string(intervalo);
            DataFrame* dfMayores = padre->filtrarDFNum(padre->obtenerCat(),intervaloStr,">");
            DataFrame* dfMenores = padre->filtrarDFNum(padre->obtenerCat(),intervaloStr,"<");
            InfoEntropia* contIGMayores = this->inicializarCont(dfMayores);
            InfoEntropia* contIGMenores = this->inicializarCont(dfMenores);
            Nodo* hijoMayores = new Nodo(dfMayores,contIGMayores,"mayor");
            Nodo* hijoMenores = new Nodo(dfMenores,contIGMenores,"menor");
            padre->agregarNodo(hijoMayores);
            padre->agregarNodo(hijoMenores);
            contador = contador+1;
            std::cout << "Dividiendo con numeros y contador " << contador << std::endl;
            this->split(hijoMayores, contador);
            this->split(hijoMenores, contador);
        }
    }
}

double Arbol::calculoInfoGainOptimoDeNumerico(DataFrame* entrenamiento, std::string nombre_atributo, double &intervalo) {

    if(entrenamiento->cantidad() < 1) {
        std::cout << "[!] DataFrame sin elementos en " << nombre_atributo << ". InfoGain = 0" << std::endl;
        return 0.0;
    }

    Crimen* primer_crimen = entrenamiento->at(0);

    double primer_valor_atributo = *(double*)primer_crimen->obtenerAtributo(nombre_atributo);

    double maxi = primer_valor_atributo;
    double mini = primer_valor_atributo;

    for (unsigned int i=1 ; i <entrenamiento->cantidad(); i++) {

        Crimen* actual = entrenamiento->at(i);
        double valor_atributo = *(double*)actual->obtenerAtributo(nombre_atributo);

        if (valor_atributo > maxi ){
            maxi = valor_atributo;
        } else if (valor_atributo < mini){
            mini = valor_atributo;
        }
    }

    intervalo = (maxi - mini)/(double)10.0;

    std::cout << "[ATRIBUTO NUMERICO] " << nombre_atributo << ": ";
    std::cout << "Max: " << maxi << "\t  ///  ";
    std::cout << "Min: " << mini << "\t  ///  ";
    std::cout << "Intervalo: " << intervalo << std::endl;

    double gananciaNum = 0;

    int indice= 0;
    double mayorGan = this->calculoInfoGainSegunIntervalo
                    (entrenamiento, nombre_atributo, (mini+intervalo*1));
    for (int i= 2 ; i < 10 ; i++){
        gananciaNum = this->calculoInfoGainSegunIntervalo(entrenamiento, nombre_atributo, (mini+intervalo*i));
        std::cout << "InfoGain candidato: \t\t" << gananciaNum << " con intervalo " << (mini+intervalo*i) <<  std::endl;
        if (mayorGan < gananciaNum) {
            mayorGan = gananciaNum;
            indice = i;
        }
    }
    intervalo = mini + intervalo*indice;
    return gananciaNum*(-1.0);
}

double Arbol::calculoInfoGainSegunIntervalo(DataFrame* entrenamiento, std::string nombre_atributo, double comparador) {

    std::map<string, TuplasCat*> frequencia_de_clase = std::map<string, TuplasCat*>();

    for(std::vector<int>::size_type i = 0; i < entrenamiento->cantidad(); i++) {
        Crimen* actual = entrenamiento->at(i);

        // Valor del atributo casteado a Double
        double valor_atributo = *(double*)actual->obtenerAtributo(nombre_atributo);

        //si es menor o igual al comparador lo agrupo con los menores, sino con los mayores
        std::string atributo_actual;

        if(valor_atributo<=comparador) {
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
    return infoGain;
}

double Arbol::calculoInfoGainCategorico(DataFrame* entrenamiento, std::string nombre_atributo){
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
    return infoGain * (-1.0);
}


double Arbol::calculoInfoTotal(DataFrame* entrenamiento, string &mayorCrimen){ //por Mati

    TuplasCat* vectorTuplas = new TuplasCat();
    for(unsigned int i = 0; i < entrenamiento->cantidad(); i++) {

        Crimen* actual = entrenamiento->at(i);

        std::string categoria_actual = *actual->obtenerCategory();
        vectorTuplas->aumentarCat(categoria_actual);
    }

    mayorCrimen = vectorTuplas->mayorCrimen();
    double infoGain = (vectorTuplas->informationGain());
    return infoGain * (-1.0);
}
