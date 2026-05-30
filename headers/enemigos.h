#ifndef ENEMIGOS_H_INCLUDED
#define ENEMIGOS_H_INCLUDED

#define RANGO_VISION 6

#include <stdbool.h>
// Para romper la dependencia circular
typedef struct Nivel Nivel;
typedef struct Jugador Jugador;

typedef enum {
    KOBOLD = 1,
    LEPRECHAUN,
    MIMIC,
    NYMPH,
    ORC
} TipoEnemigo;


typedef struct {
    int x; // Posicion horizontal actual en la matriz
    int y; // Posicion vertical actual en la matriz
    int hp;
    int hpMax;
    int attack; // Daño que inflige el enemigo
    int tipo; // Tipo de enemigo
    char representacion;
} Enemigo;

void spawnearEnemigo(Nivel* nivel, Enemigo* enemigo);
bool localizarYMoverAJugador(Nivel* nivel, Enemigo* enemigo, Jugador* jugador);
void atacarAJugador(Enemigo* enemigo, Jugador* jugador);
void determinarCantidadEnemigos(Nivel* nivel);
void determinarTipoEnemigo(Enemigo* enemigo);
void eleminarEnemigo(Nivel* nivel, Enemigo* enemigo);
int buscarEnemigoEnPosicion(Nivel* nivel, int x, int y);

#endif // ENEMIGOS_H_INCLUDED
