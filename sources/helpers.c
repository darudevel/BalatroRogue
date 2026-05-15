#include <stdlib.h>
#include <stdio.h>
#include "../headers/helpers.h"

int h_numAleatorio(int min, int max)
{
    return (rand()%(max - min + 1)) + min;
}

void h_limpiarColor()
{
    printf(COLOR_DEFAULT);
}
