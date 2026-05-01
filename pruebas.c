#include "headers/mapa.h"
#include "headers/matriz_dinamica.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
    Nivel nivel;
    int running=1;

    while(running)
    {
    system("cls");
    srand(time(NULL));

    // Marcos: nivel.ancho >= 6*nivel.columnas && nivel.alto >= 6*nivel.filas sino se rompe el programa.
    // Creo que es por algo de que sino queda un numero negativo en sectorW y/o sectorH que luego van al NumeroAleatorio() y
    // eso a c parece no gustarle mucho.
    // Ej: mapa 9x9 con sectores 3x3 no funciona, pero mapa 100x40 con sectores 5x2 si funciona

    printf("Ancho del mapa: ");
    scanf("%d", &nivel.ancho);

    printf("Alto del mapa: ");
    scanf("%d", &nivel.alto);

    printf("Cantidad de sectores verticales del mapa: ");
    scanf("%d", &nivel.columnas);

    printf("Cantidad de sectores horizontales del mapa: ");
    scanf("%d", &nivel.filas);

    nivel.mapa = CrearMatrizChar(nivel.alto, nivel.ancho);

    system("cls");

    generarNivel(nivel);

    MostrarMatriz(nivel);

    LiberarMatrizChar(nivel.mapa, nivel.alto);

    scanf("%d", &running);
    }

    return 0;
}
