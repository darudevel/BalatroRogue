#include "headers/matriz_dinamica.h"

void** crearMatriz(int fil, int col, size_t tamElem)
{
    void** mat = malloc(sizeof(void*) * fil);

    if(!mat)
    {
        return NULL;
    }

    void** ult = mat + fil - 1;

    for(void** i = mat; i <= ult; i++)
    {
        *i = malloc(tamElem * col);

        if(!*i)
        {
            destruirMatriz(mat, i - mat);
            return NULL;
        }
    }

    return mat;
}


void destruirMatriz(void** mat, int fil)
{
    void** ult = mat + fil - 1;

    for(void** i = mat; i <= ult; i++)
    {
        free(*i);
    }

    free(mat);
}

