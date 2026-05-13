#include <stdlib.h>
#include "../headers/helpers.h"

int NumeroAleatorio(int min, int max)
{
    return (rand()%(max - min + 1)) + min;
}
