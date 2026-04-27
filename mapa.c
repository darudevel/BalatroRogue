#include "mapa.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// TODO: Definir NumeroAleatorio en un archivo donde tenga mas sentido que este
int NumeroAleatorio(int min, int max)
{
    return (rand()%(max - min + 1)) + min;
}

void MostrarMatriz(char mapa[ANCHO_INICIAL][ALTO_INICIAL])
{
    for (int y = 0; y < ALTO_INICIAL; y++) {
        if(y) printf("\n");
        for (int x = 0; x < ANCHO_INICIAL; x++) {
            printf("%c", mapa[y][x]);
        }
    }
}

void inicializarMapa(char mapa[ANCHO_INICIAL][ALTO_INICIAL])
{
   for (int y = 0; y < ALTO_INICIAL; y++) {
        for (int x = 0; x < ANCHO_INICIAL; x++) {
            mapa[y][x] = ' ';
        }
    }
}

void generarNivel(char mapa[ANCHO_INICIAL][ALTO_INICIAL])
{
    inicializarMapa(mapa);
    Habitacion habs[FILAS][COLS];
    srand(time(NULL));

    int sectorW = ANCHO_INICIAL / COLS; // TODO: despues reemplazar el ancho_inicial con el tamanio dinamico cuando tengamos eso implementado
    int sectorH = ALTO_INICIAL / FILAS;

    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLS; c++) {
            Habitacion hab;

            hab.sectorX = c;
            hab.sectorY = f;

            // minimo de 4 para una habitacin 2x2
            // maximo de sectorW/H - 2 para que la habitacion entre en el sector sin que este pegado en el borde
            hab.w = NumeroAleatorio(4, sectorW - 2);
            hab.h = NumeroAleatorio(4, sectorH - 2);

            // x e y en posiciones aleatorias pero dejando espacio para los pasillos
            hab.x = (c * sectorW) + NumeroAleatorio(1, sectorW - hab.w - 1);
            hab.y = (f * sectorH) + NumeroAleatorio(1, sectorH - hab.h - 1);

            generarHabitacion(mapa, hab);
            habs[f][c] = hab;

            if(c-1 >= 0)
                conectarHabitaciones(mapa, hab, habs[f][c-1]);
            if(f-1 >= 0)
                conectarHabitaciones(mapa, hab, habs[f-1][c]);
        }
    }
}

void generarHabitacion(char mapa[ANCHO_INICIAL][ALTO_INICIAL], Habitacion h)
{
    for (int y = h.y; y < (h.y + h.h); y++) {
        for (int x = h.x; x < (h.x + h.w); x++) {
            if(y==h.y || y==h.y + h.h - 1)
                mapa[y][x] = '-'; // Poner las paredes horizontales
            else if
                (x==h.x || x==h.x + h.w - 1) mapa[y][x] = '|'; // Poner las paredes verticales
            else
                mapa[y][x] = '.'; // Poner piso
        }
    }
}

// Solo funciona si las habitaciones estan en sectores adyacentes
void conectarHabitaciones(char mapa[ANCHO_INICIAL][ALTO_INICIAL], Habitacion h1, Habitacion h2)
{
    int horizontal = (h1.sectorX != h2.sectorX) ? 1 : 0;
    int p1x, p1y, p2x, p2y, pMedio;

    // Marcos: Seleccionar 2 puntos en las pardes mas cercanas de las habitaciones a unir
    if(horizontal)
    {
        if(h1.sectorX < h2.sectorX)
        {
            p1x = h1.x + h1.w - 1;
            p1y = NumeroAleatorio(h1.y + 1, h1.y + h1.h - 2);
            p2x = h2.x;
            p2y = NumeroAleatorio(h2.y + 1, h2.y + h2.h - 2);
        }
        else
        {
            p1x = h1.x;
            p1y = NumeroAleatorio(h1.y + 1, h1.y + h1.h - 2);
            p2x = h2.x + h2.w - 1;
            p2y = NumeroAleatorio(h2.y + 1, h2.y + h2.h - 2);
        }
        pMedio = (p1x + p2x)/2;
    }
    else
    {
        if(h1.sectorY < h2.sectorY)
        {
            p1x = NumeroAleatorio(h1.x + 1, h1.x + h1.w - 2);
            p1y = h1.y + h1.h - 1;
            p2x = NumeroAleatorio(h2.x + 1, h2.x + h2.w - 2);
            p2y = h2.y;
        }
        else
        {
            p1x = NumeroAleatorio(h1.x + 1, h1.x + h1.w - 2);
            p1y = h1.y;
            p2x = NumeroAleatorio(h2.x + 1, h2.x + h2.w - 2);
            p2y = h2.y + h2.h - 1;
        }
        pMedio = (p1y + p2y)/2;
    }

    mapa[p1y][p1x] = '+';
    mapa[p2y][p2x] = '+';

    // Marcos: Hacer un camino tipo 'Z' dependiendo de la posicion de las habitaciones
    if(horizontal)
    {
        while(p1x != pMedio)
        {
            if(mapa[p1y][p1x] == ' ')
                mapa[p1y][p1x] = '#';
            p1x += (p1x < pMedio) ? 1 : -1;
        }

        while(p1y != p2y)
        {
            if(mapa[p1y][p1x] == ' ')
                mapa[p1y][p1x] = '#';
            p1y += (p1y < p2y) ? 1 : -1;
        }

        while(p1x != p2x)
        {
            if(mapa[p1y][p1x] == ' ')
                mapa[p1y][p1x] = '#';
            p1x += (p1x < p2x) ? 1 : -1;
        }
    }
    else
    {
        while(p1y != pMedio)
        {
            if(mapa[p1y][p1x] == ' ')
                mapa[p1y][p1x] = '#';
            p1y += (p1y < pMedio) ? 1 : -1;
        }

        while(p1x != p2x)
        {
            if(mapa[p1y][p1x] == ' ')
                mapa[p1y][p1x] = '#';
            p1x += (p1x < p2x) ? 1 : -1;
        }

        while(p1y != p2y)
        {
            if(mapa[p1y][p1x] == ' ')
                mapa[p1y][p1x] = '#';
            p1y += (p1y < p2y) ? 1 : -1;
        }
    }
}
