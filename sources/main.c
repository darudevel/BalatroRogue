#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../headers/mapa.h"
#include "../headers/personaje.h"
#include "../headers/juego.h"
#include "../headers/helpers.h"

int main()
{
    srand(time(NULL));

    Juego   juego;
    Jugador jugador;
    Nivel   nivel;

    juego.nivel   = &nivel;
    juego.jugador = &jugador;

    bool loop_juego = true;
    EstadoJuego estado_partida = JUGANDO;
    char tecla;
    while(loop_juego) {
        if (estado_partida == VICTORIA) {
            ganarPartida(&juego);
        }
        estado_partida = inicializarJuego(&juego);

        while(estado_partida == JUGANDO){
            esperarInput(&tecla);
            estado_partida = tickJuego(&juego, tecla);

            // Dario: si se generó el amuleto y estas pisando la escalera, ganas
            // no hace falta checkear si estas en el piso mas bajo porque esta implicito en que este generado el amuleto
            if (jugador.escalera && jugador.puede_ganar) {
                estado_partida = VICTORIA;
            } else if (jugador.escalera && nivel.profundidad == nivel.profundidad_max) { // Si llegas aca, no podes ganar y pisaste la escalera
                printf("\n" ROJO "DEBES OBTENER " VERDE "El Amuleto de Yendor" ROJO " PARA SALIR DE ESTE PISO." COLOR_DEFAULT);
            } else if (jugador.escalera){
                nuevoPiso(&juego);
            }
            jugador.escalera = false;
        }

        if(jugador.hp <= 0){
            printf("\n\n\tHP: "ROJO"%d/%d "COLOR_DEFAULT" | Str: %d | G: %d | H: %d/%d",
                0, jugador.hpMax, jugador.danio, jugador.oro, jugador.hambre, jugador.hambre_max);
            printf("\n\t"ROJO"HAS MUERTO"COLOR_DEFAULT);
            printf("\nPresione cualquier tecla para volver al menu principal: ");
            esperarInput(&tecla);
        }


    }

    salirJuego(&juego);
    return 0;
}
