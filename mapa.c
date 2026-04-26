#include "mapa.h"
#include <time.h>
#include <stdlib.h>

void inicializarMapa(char **mapa)
{
   for (int y = 0; y < ALTO_INICIAL; y++) {
        for (int x = 0; x < ANCHO_INICIAL; x++) {
            mapa[y][x] = ' ';
        }
    }
}

void generarNivel(char **mapa)
{

    inicializarMapa(mapa);
    Habitacion habs[FILAS * COLS];
    int cantidad = 0;

    int sectorW = ANCHO_INICIAL / COLS; // TODO: despues reemplazar el ancho_inicial con el tamanio dinamico cuando tengamos eso implementado
    int sectorH = ALTO_INICIAL / FILAS;

    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLS; c++) {
            Habitacion hab;
            // +4 para tener como minimo de tamanio 4x4
            // el -6 para asegurarnos de que queda todo adentro del sector y no se pegotea con otra habitacion
            hab.w = (rand() % (sectorW - 6)) + 4; 
            hab.h = (rand() % (sectorW - 6)) + 4;

            // x e y en posiciones aleatorias pero dejando espacio para los pasillos
            hab.x = (c * sectorW) + (rand() % (sectorW - hab.w - 1)) + 1;
            hab.y = (f * sectorW) + (rand() % (sectorW - hab.w - 1)) + 1;

            hab.centroX = hab.x + (hab.w / 2);
            hab.centroY = hab.y + (hab.h / 2);

            generarHabitacion(mapa, hab);
            habs[cantidad] = hab;

            if (cantidad > 0) {
                conectarHabitaciones(mapa, habs[cantidad - 1], habs[cantidad]);
            }
            cantidad++;
        }
    }

    // daru: conectar la ultima con la primera (no estoy seguro de si esto esta bien)
    // conectarHabitaciones(mapa, habs[cantidad - 1], habs[0]);

}

void generarHabitacion(char **mapa, Habitacion h)
{
    for (int y = h.y; y < (h.y + h.h); y++) {
        for (int x = h.x; x < (h.x + h.w); x++) {
            mapa[y][x] = '.';
        }
    }
}

void conectarHabitaciones(char **mapa, Habitacion h1, Habitacion h2)
{
    int x = h1.centroX;
    int y = h1.centroY;

    // desde la habitacion 1 hasta la habitacion 2, primero horizontal y despues vertical desde el centro
    while (x != h2.centroX) {
        if (mapa[y][x] ==  ' ') 
            mapa[y][x] = '#'; // pasillo
        x += (h2.centroX > x) ? 1 : -1;
    }

    while (y != h2.centroY) {
        if (mapa[y][x] ==  ' ') 
            mapa[y][x] = '#';
        y += (h2.centroY > y) ? 1 : -1;
    }
}

