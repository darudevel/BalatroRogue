#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED

#include <stdbool.h>
#include <time.h>
#include "enemigos.h"
#include "objetos.h"
// Para romper la dependencia circular
typedef struct Nivel Nivel;

typedef struct Jugador {
    int x; // Posicion horizontal actual en la matriz
    int y; // Posicion vertical actual en la matriz

    int hp;
    int hpMax;

    int hambre;
    int hambre_max;
    int tick_hambre;
    int proximo_tick_hambre;

    int oro;
    Inventario inventario;
    int danio;

    bool escalera;
    bool puede_ganar; // si tiene el amuleto
    // Estadisticas
    int enemigos_asesinados;
    int objetos_recogidos;
} Jugador;

// Busca un casillero vacio de habitacion ('.') y situa al jugador ahi
void spawnearJugador(Nivel* nivel, Jugador* jugador);

// Marcos: separo las funciones inicializar de spawnear para cuando tengamos mas niveles solo usar spawnear
void inicializarJugador(Jugador* jugador);

// Intenta mover al jugador en una direccion (dx, dy).
// dx/dy pueden ser: -1 (izquierda/arriba), 1 (derecha/abajo) o 0 (quieto).
bool moverJugador(Nivel* nivel, Jugador* jugador, int dx, int dy);

int atacarAEnemigo(Nivel* nivel, Enemigo* enemigo, Jugador* jugador);

#endif // PERSONAJE_H_INCLUDED
