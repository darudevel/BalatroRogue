#ifndef MATRIZ_DINAMICA_H
#define MATRIZ_DINAMICA_H

#include <stdlib.h>

void** crearMatriz(size_t filas, size_t columnas, size_t tam_dato);
void   liberarMatriz(void** matriz, size_t filas);

#endif // MATRIZ_DINAMICA_H
