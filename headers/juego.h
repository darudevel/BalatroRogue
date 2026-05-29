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

typedef struct {
    int ancho_nivel;
    int alto_nivel;
    int profundidad_max;
    int enemigos_reducidos;
} Configuracion;

void inicializarJuego(Juego *juego);
void menuPrincipal(Configuracion *config);
void menuConfiguracion(Configuracion *config);
int validarInput(int rango_min, int rango_max);

#endif // JUEGO_H_INCLUDED