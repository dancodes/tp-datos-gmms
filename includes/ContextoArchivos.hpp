#pragma once

class DataFrame;

class ContextoArchivos {
public:
    DataFrame* obtenerEntrenamiento();
    DataFrame* obtenerIncognitas();
};
