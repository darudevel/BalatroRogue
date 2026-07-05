#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include <stdbool.h>

// Para romper la dependencia circular
typedef struct Nivel Nivel;
typedef struct Jugador Jugador;

typedef enum {
    DERROTA,
    JUGANDO,
    VICTORIA
} EstadoJuego;

typedef struct {
    Nivel *nivel;
    Jugador *jugador;
} Juego;

typedef struct Configuracion{
    int ancho_nivel;
    int alto_nivel;
    int profundidad_max;
    int enemigos_reducidos;
} Configuracion;

EstadoJuego inicializarJuego(Juego *juego);
void nuevoPiso(Juego* juego);
void menuPrincipal(Configuracion *config);
void menuConfiguracion(Configuracion *config);
void menuCaracteres(void);
int validarInput(int rango_min, int rango_max);
void esperarInput(char* tecla);
EstadoJuego tickJuego(Juego* juego, char tecla);
void ganarPartida(Juego *juego);
void salirJuego(Juego* juego);

#endif // JUEGO_H_INCLUDED
