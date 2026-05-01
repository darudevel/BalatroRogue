#include "headers/matriz_dinamica.h"

char** CrearMatrizChar(size_t filas, size_t columnas)
{
    char** Matriz;

    Matriz = malloc(sizeof(char*)*filas);
    if(!Matriz)
    {
        free(Matriz);
        return NULL;
    }

    for(size_t i=0; i<filas; i++)
    {
        *(Matriz+i) = malloc(sizeof(char)*columnas);
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

void LiberarMatrizChar(char** Matriz, size_t filas)
{
    filas--;

    for(filas; filas>0; filas--)
        free(*(Matriz+filas));
    free(*Matriz);

    free(Matriz);
}

Habitacion** CrearMatrizHab(size_t filas, size_t columnas)
{
    Habitacion** Matriz;

    Matriz = malloc(sizeof(Habitacion*)*filas);
    if(!Matriz)
    {
        free(Matriz);
        return NULL;
    }

    for(size_t i=0; i<filas; i++)
    {
        *(Matriz+i) = malloc(sizeof(Habitacion)*columnas);
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

void LiberarMatrizHab(Habitacion** Matriz, size_t filas)
{
    filas--;

    for(filas; filas>0; filas--)
        free(*(Matriz+filas));
    free(*Matriz);

    free(Matriz);
}
