#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "../headers/objetos.h"
#include "../headers/enemigos.h"

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
    int cant_objetos;
    Objeto oro[MAX_ORO_NIVEL];
    int cant_oro;
    Objeto amuleto;
    int amuleto_generado;

    int profundidad;
    int profundidad_max;

    Enemigo* vect_enemigos;
    int cant_enemigos;
    int enemigos_reducidos;
} Nivel;

void inicializarMapa(Nivel* nivel);
Nivel inicializarNivel(int ancho, int alto, int enemigos_reducidos, int profundidad_max);
void generarNivel(Nivel* nivel);
void generarEscalera(Nivel *nivel);
void generarHabitacion(Nivel* nivel, Habitacion* h);
void generarPasillos(Nivel* nivel, Habitacion* h1, Habitacion* h2);
void conectarHabitaciones(Nivel* nivel);
void dfsConectar(Nivel* nivel, int, int, int**);
void mostrarNivel(Nivel* nivel);

#endif // MAPA_H_INCLUDED
