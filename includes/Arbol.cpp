#include "Arbol.hpp"


contenedor Arbol::inicializarCont(DataFrame* entrenamiento){
    contenedor cont;
    cont.iGTot = this->calculoInfoTotal(entrenamiento, cont.mayorCrimen);
    cont.iGDP = this->calculoInfoGainCategorico(entrenamiento, "pd");
    cont.iGX = this->calculoInfoGainOptimoDeNumerico(entrenamiento,std::string("x"), cont.intervaloX);
    cont.iGY = this->calculoInfoGainOptimoDeNumerico(entrenamiento,std::string("y"), cont.intervaloY);
    return cont;
}

Arbol::Arbol(DataFrame* entrenamiento){
    std::string atribIncial = "raiz";
    contenedor contIG = this->inicializarCont(entrenamiento);
    inicio = new Nodo(entrenamiento, contIG, atribIncial);
    unsigned int contador = 0;
    this->split(inicio, contador);
}

bool Arbol::seguir(int contador, string cat){
    //falta agregarla la otra condicion de corte
    int piso = 100;
    return (contador<piso) && (cat != "cat");
}

void Arbol::split(Nodo* padre, unsigned int contador) {
    std::string district = "pdDistrict";

    if (this->seguir(contador, padre->obtenerCat())) {

        if(padre->obtenerCat() == district) {
            
            std::vector<std::string>* atribHijos = padre->obtenerListaAtrib();
            for (int i=0;atribHijos->size();i++){
                DataFrame* df = padre->filtrarDFPD(district,atribHijos->at(i));
                contenedor contIG = this->inicializarCont(df);
                Nodo* hijo = new Nodo(df,contIG,atribHijos->at(i));
                contador = contador++;
                this->split(hijo, contador);

            }
        } else {
            double intervalo = padre->obtenerIntervalo();
            std::string intervaloStr = std::to_string(intervalo);
            DataFrame* dfMayores = padre->filtrarDFNum(padre->obtenerCat(),intervaloStr,">");
            DataFrame* dfMenores = padre->filtrarDFNum(padre->obtenerCat(),intervaloStr,"<");
            contenedor contIGMayores = this->inicializarCont(dfMayores);
            contenedor contIGMenores = this->inicializarCont(dfMenores);
            Nodo* hijoMayores = new Nodo(dfMayores,contIGMayores,"mayor");
            Nodo* hijoMenores = new Nodo(dfMenores,contIGMenores,"menor");
            contador = contador++;
            this->split(hijoMayores, contador);
            this->split(hijoMenores, contador);
        }
    }
}

double Arbol::calculoInfoGainOptimoDeNumerico(DataFrame* entrenamiento, std::string nombre_atributo, double &intervalo) {

    Crimen* primer_crimen = entrenamiento->at(0);
    double primer_valor_atributo = *(double*)primer_crimen->obtenerAtributo(nombre_atributo);

    double maxi = primer_valor_atributo;
    double mini = primer_valor_atributo;

    for (unsigned int i=1 ; i < entrenamiento->cantidad() ; i++) {

        Crimen* actual = entrenamiento->at(i);
        double valor_atributo = *(double*)actual->obtenerAtributo(nombre_atributo);

        if (valor_atributo > maxi ){
            maxi = valor_atributo;
        } else if (valor_atributo < mini){
            mini = valor_atributo;
        }
    }

    intervalo = (maxi - mini)/10;
    double mayorGan = 0;
    double gananciaNum = 0;

    int indice= 0;

    for (int i= 1 ; i < 10 ; i++){
        gananciaNum = calculoInfoGainSegunIntervalo(entrenamiento, nombre_atributo, (mini+intervalo*i));

        if (mayorGan < gananciaNum) {
            mayorGan = gananciaNum;
            indice = i;
        }
    }
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
        } else {
                frequencia_de_clase[atributo_actual]->aumentarCat(categoria_actual);
        }
    }
    double infoGain = 0;
    // show content:
    for (std::map<string, TuplasCat*>::iterator it=frequencia_de_clase.begin(); it!=frequencia_de_clase.end(); ++it) {
        infoGain = infoGain + (it->second->informationGain() *
                    (it->second->obtenerTotal() / entrenamiento->cantidad()));
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
