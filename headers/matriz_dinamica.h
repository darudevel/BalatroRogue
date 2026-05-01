#ifndef MATRIZ_DINAMICA_H
#define MATRIZ_DINAMICA_H

#include <stdlib.h>
#include "mapa.h"

char** CrearMatrizChar(size_t, size_t);
void LiberarMatrizChar(char**, size_t);

Habitacion** CrearMatrizHab(size_t, size_t);
void LiberarMatrizHab(Habitacion**, size_t);

#endif // MATRIZ_DINAMICA_H
