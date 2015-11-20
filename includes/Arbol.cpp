#include "Arbol.hpp"


contenedor Arbol::InicializarCont(DataFrame* entrenamiento){
    contenedor cont;
    cont.iGTot = calculoInfoTotal(entrenamiento);
    cont.iGDP = this->calculoInfoGainDP(entrenamiento);
    cont.iGX = this->calculoInfoGainXoY(entrenamiento,'x', cont.intervaloX);
    cont.iGY = this->calculoInfoGainXoY(entrenamiento,'y',cont.intervaloY);
    return cont;
}

Arbol::Arbol(DataFrame* entrenamiento){
    std::string atribIncial = "raiz";
    contenedor contIG = InicializarCont(entrenamiento);
    inicio = new Nodo(entrenamiento, contIG, atribIncial);
    unsigned int contador = 0;
    Split(inicio, contador);
}

bool Arbol::Seguir(int contador){
    //falta agregarla la otra condicion de corte
    int piso = 100;
    bool seguir=(contador<piso);
    return seguir;
}

void Arbol:: Split(Nodo* padre, unsigned int contador){
    std::string district = "pdDistrict";
    if (Seguir(contador)){
        if(padre->obtenerCat() == district){
            std::vector<std::string>* atribHijos = padre->obtenerListaAtrib();
            for (int i=0;atribHijos->size();i++){
                DataFrame* df = padre->filtrarDFPD(district,atribHijos->at(i));
                contenedor contIG = InicializarCont(df);
                Nodo* hijo = new Nodo(df,contIG,atribHijos->at(i));
                contador = contador++;
                Split(hijo, contador);
            }
        }else{
            double intervalo = padre->obtenerIntervalo();
            std::string intervaloStr = std::to_string(intervalo);
            DataFrame* dfMayores = padre->filtrarDFNum(padre->obtenerCat(),intervaloStr,">");
            DataFrame* dfMenores = padre->filtrarDFNum(padre->obtenerCat(),intervaloStr,"<");
            contenedor contIGMayores = InicializarCont(dfMayores);
            contenedor contIGMenores = InicializarCont(dfMenores);
            Nodo* hijoMayores = new Nodo(dfMayores,contIGMayores,"mayor");
            Nodo* hijoMenores = new Nodo(dfMenores,contIGMenores,"menor");
            contador = contador++;
            Split(hijoMayores, contador);
            Split(hijoMenores, contador);
        }
    }
}

double Arbol::calculoInfoGainXoY(DataFrame* entrenamiento, char c, double &intervalo) {
    double maxi = (entrenamiento->at(0))->obtenerNumerico(c);
    double mini = (entrenamiento->at(0))->obtenerNumerico(c);
    for (unsigned int i=1 ; i < entrenamiento->cantidad() ; i++){
        if (((entrenamiento->at(i)))->obtenerNumerico(c) > maxi ){
            maxi = ((entrenamiento->at(i)))->obtenerNumerico(c);
        }
        if ((entrenamiento->at(i))->obtenerNumerico(c) < mini ){
            mini = (entrenamiento->at(i))->obtenerNumerico(c);
        }
    }
    intervalo = (maxi - mini)/10;
    double mayorGan = 0;
    double gananciaNum = 0;
    int indice= 0;
    for (int i= 1 ; i < 10 ; i++){
        gananciaNum = calculoInfoGainNumerico(entrenamiento, (mini+intervalo*i));
        if (mayorGan < gananciaNum) {
            mayorGan = gananciaNum;
            indice = i;
        }
    }
    return gananciaNum*(-1.0);
}

double Arbol::calculoInfoGainNumerico(DataFrame* entrenamiento , double comparador) {
    std::map<string, TuplasCat*> frequencia_de_clase = std::map<string, TuplasCat*>();
    for(std::vector<int>::size_type i = 0; i < entrenamiento->cantidad(); i++) {
        Crimen* actual = entrenamiento->at(i);
            //si es menor o igual al comparador lo agrupo con los menores, sino con los mayores
        std::string atributo_actual;
            if(actual->obtenerX()<=comparador){
                atributo_actual = "menor";
            }else{
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

double Arbol::calculoInfoGainDP(DataFrame* entrenamiento){
    std::map<string, TuplasCat*> frequencia_de_clase = std::map<string, TuplasCat*>();

    for(unsigned int i = 0; i < entrenamiento->cantidad(); i++) {

        Crimen* actual = entrenamiento->at(i);
        std::string atributo_actual = *actual->obtenerPd();
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


double Arbol::calculoInfoTotal(DataFrame* entrenamiento){ //por Mati

    TuplasCat* vectorTuplas = new TuplasCat();
    for(unsigned int i = 0; i < entrenamiento->cantidad(); i++) {

        Crimen* actual = entrenamiento->at(i);
        std::string categoria_actual = *actual->obtenerCategory();


        vectorTuplas->aumentarCat(categoria_actual);
    }
    double infoGain = (vectorTuplas->informationGain());
    return infoGain * (-1.0);
}
