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

    bool bool_juego = true;
    EstadoJuego estado_partida = JUGANDO;
    char tecla;
    while(bool_juego){
        estado_partida = inicializarJuego(&juego);

        while(estado_partida){
            esperarInput(&tecla);
            estado_partida = tickJuego(&juego, tecla);
            if(jugador.escalera == true){
                nuevoPiso(&juego);
                jugador.escalera = false;
            }
        }

        if(jugador.hp <= 0){
            printf("\n\n\tHP: "ROJO"%d/%d "COLOR_DEFAULT" | Str: %d | G: %d",
                0, jugador.hpMax, jugador.danio, jugador.oro);
            printf("\n\t"ROJO"HAS MUERTO"COLOR_DEFAULT);
            printf("\nPresione cualquier tecla para volver al menu principal: ");
            esperarInput(&tecla);
        }
    }

    salirJuego(&juego);
    return 0;
}
