#include <stdlib.h>
#include "../headers/Matriz_Dinamica.h"

void** CrearMatriz(size_t filas, size_t columnas, size_t TamDato)
{
    void** Matriz;

    Matriz = malloc(sizeof(void*)*filas);
    if(!Matriz)
    {
        free(Matriz);
        return NULL;
    }

    for(size_t i=0; i<filas; i++)
    {
        *(Matriz+i) = malloc(TamDato*columnas);
        if(!(*(Matriz+i)))
        {
            for(i; i>0; i--)
            {
                free(*(Matriz+i));
            }
            free(*Matriz);
            free(Matriz);
            return NULL;
        }
    }

    return Matriz;
}

void LiberarMatriz(void** Matriz, size_t filas)
{
    filas--;

    for(filas; filas>0; filas--)
        free(*(Matriz+filas));
    free(*Matriz);

    free(Matriz);
}
