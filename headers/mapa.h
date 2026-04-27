#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#define ANCHO_INICIAL 60
#define ALTO_INICIAL 60

// TODO: ver que numero queda bien
#define FILAS 3
#define COLS 3

typedef struct
{
    int x, y, w, h;
    int sectorX, sectorY;
} Habitacion;

// Marcos: MostrarMatriz y NumeroAleatorio creo que no deberian de ir aca, pero no se donde mas ponerlo xd
void MostrarMatriz(char[ANCHO_INICIAL][ALTO_INICIAL]);

// daru: posiblemente cambiemos todas estas firmas porque todavia no hicimos consenso de como hacer la estructura de juego y todo eso jeee
void inicializarMapa(char[ANCHO_INICIAL][ALTO_INICIAL]);
void generarNivel(char[ANCHO_INICIAL][ALTO_INICIAL]);
void generarHabitacion(char[ANCHO_INICIAL][ALTO_INICIAL], Habitacion);
void conectarHabitaciones(char[ANCHO_INICIAL][ALTO_INICIAL], Habitacion, Habitacion);

int NumeroAleatorio(int, int);

#endif // MAPA_H_INCLUDED
