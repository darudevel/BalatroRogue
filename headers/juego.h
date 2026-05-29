#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "../headers/mapa.h"

typedef enum {
    MENU_PRINCIPAL,
    TIENDA,
    JUGANDO,
    FIN
} EstadoJuego;

typedef struct {
    Nivel *nivel;
    Jugador *jugador;
} Juego;

void inicializarJuego(Juego *juego);

#endif // JUEGO_H_INCLUDED