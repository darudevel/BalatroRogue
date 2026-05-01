#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

typedef struct
{
    int x, y, w, h;
    int sectorX, sectorY;
} Habitacion;

typedef struct
{
    char** mapa;
    int ancho, alto, filas, columnas;
} Nivel;

// Marcos: MostrarMatriz y NumeroAleatorio creo que no deberian de ir aca, pero no se donde mas ponerlo xd
void MostrarMatriz(Nivel);

// daru: posiblemente cambiemos todas estas firmas porque todavia no hicimos consenso de como hacer la estructura de juego y todo eso jeee
void inicializarMapa(Nivel);
void generarNivel(Nivel);
void generarHabitacion(Nivel, Habitacion);
void conectarHabitaciones(Nivel, Habitacion, Habitacion);

int NumeroAleatorio(int, int);

#endif // MAPA_H_INCLUDED
