#ifndef ENEMIGOS_H_INCLUDED
#define ENEMIGOS_H_INCLUDED
#include "../headers/personaje.h"
#include "../headers/mapa.h"

typedef struct {
    int x; // Posicion horizontal actual en la matriz
    int y; // Posicion vertical actual en la matriz
    int hp;
    int hpMax;
    int atack; // Daño que inflige el enemigo
    int tipo; // Tipo de enemigo
} Enemigo;

void spawnearEnemigo(Nivel* nivel, Enemigo* enemigo);
void localizarymoverjugador(Nivel* nivel, Enemigo* enemigo, Jugador* jugador);
void atacarajugador(Enemigo* enemigo, Jugador* jugador);
int cantidadEnemigos(Habitacion* habitacion);
void tipoenemigo(Enemigo* enemigo);
void eleminarEnemigo(Nivel* nivel, Enemigo* enemigo);


#endif // ENEMIGOS_H_INCLUDED
