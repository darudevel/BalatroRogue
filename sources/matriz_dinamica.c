#include <stdlib.h>
#include "../headers/matriz_dinamica.h"

void** crearMatriz(size_t filas, size_t columnas, size_t tam_dato)
{
    void** matriz;

    matriz = malloc(sizeof(void*)*filas);
    if(!matriz)
    {
        free(matriz);
        return NULL;
    }

    for(size_t i=0; i<filas; i++)
    {
        *(matriz+i) = malloc(tam_dato*columnas);
        if(!(*(matriz+i)))
        {
            for(i; i>0; i--)
            {
                free(*(matriz+i));
            }
            free(*matriz);
            free(matriz);
            return NULL;
        }
    }

    return matriz;
}

void liberarMatriz(void** matriz, size_t filas)
{
    filas--;

    for(filas; filas>0; filas--)
        free(*(matriz+filas));
    free(*matriz);

    free(matriz);
}
