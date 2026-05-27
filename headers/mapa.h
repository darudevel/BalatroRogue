#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "objetos.h"

typedef struct
{
    int x, y, w, h;
    int sectorX, sectorY;
} Habitacion;

typedef struct Nivel
{
    char** mapa;
    int ancho, alto, filas, columnas;
    Habitacion** habitaciones;

    Objeto objetos[MAX_OBJETOS_NIVEL];
    int cantObjetos;
    Objeto oro[MAX_ORO_NIVEL];
    int cantOro;
    Objeto amuleto;
    int amuletoGenerado;
} Nivel;

void inicializarMapa(Nivel* nivel);
void generarNivel(Nivel* nivel);
Nivel inicializarNivel(int ancho, int alto, int filas, int columnas);
void generarHabitacion(Nivel* nivel, Habitacion* h);
void conectarHabitaciones(Nivel* nivel);
void dfsConectar(Nivel* nivel, int, int, int**);
void generarPasillos(Nivel* nivel, Habitacion* h1, Habitacion* h2);
void mostrarNivel(Nivel* nivel);

#endif // MAPA_H_INCLUDED
