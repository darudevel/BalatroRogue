#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED

#include "mapa.h"
#include "objetos.h"

typedef struct Jugador {
    int x; // Posicion horizontal actual en la matriz
    int y; // Posicion vertical actual en la matriz
    int hp;
    int hpMax;
    int oro;
    Inventario inventario;
} Jugador;

// Busca un casillero vacio de habitacion ('.') y situa al jugador ahi
void spawnearJugador(Nivel* nivel, Jugador* jugador);

// Marcos: separo las funciones inicializar de spawnear para cuando tengamos mas niveles solo usar spawnear
void inicializarJugador(Jugador* jugador);

// Intenta mover al jugador en una direccion (dx, dy).
// dx/dy pueden ser: -1 (izquierda/arriba), 1 (derecha/abajo) o 0 (quieto).
char moverJugador(Nivel* nivel, Jugador* jugador, int dx, int dy);

#endif // PERSONAJE_H_INCLUDED
