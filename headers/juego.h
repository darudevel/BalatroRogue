#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include <stdbool.h>

// Para romper la dependencia circular
typedef struct Nivel Nivel;
typedef struct Jugador Jugador;

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

typedef struct Configuracion{
    int ancho_nivel;
    int alto_nivel;
    int profundidad_max;
    int enemigos_reducidos;
} Configuracion;

bool inicializarJuego(Juego *juego);
void menuPrincipal(Configuracion *config);
void menuConfiguracion(Configuracion *config);
int validarInput(int rango_min, int rango_max);
void esperarInput(char* tecla);
bool tickJuego(Juego* juego, char tecla);
void salirJuego(Juego* juego);

#endif // JUEGO_H_INCLUDED
