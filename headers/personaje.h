#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED

#include "mapa.h"

typedef struct {
    int x; // Posición horizontal actual en la matriz
    int y; // Posición vertical actual en la matriz
    int hp;
    int hpMax;
} Jugador;

// Busca un casillero vacío de habitación ('.') y sitúa al jugador ahí
void spawnearJugador(Nivel nivel, Jugador* jugador);

// Intenta mover al jugador en una dirección (dx, dy).
// dx/dy pueden ser: -1 (izquierda/arriba), 1 (derecha/abajo) o 0 (quieto).
void moverJugador(Nivel nivel, Jugador* jugador, int dx, int dy);

#endif // PERSONAJE_H_INCLUDED
