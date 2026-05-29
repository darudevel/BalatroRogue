#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h> // Necesario en Windows para usar getch() sin presionar Enter
#include "../headers/mapa.h"
#include "../headers/matriz_dinamica.h"
#include "../headers/personaje.h"
#include "../headers/helpers.h"
#include "../headers/objetos.h"
#include "../headers/juego.h"

int main()
{
    srand(time(NULL));
    
    Juego   juego;
    Jugador jugador;
    Nivel   nivel;

    juego.nivel   = &nivel;
    juego.jugador = &jugador;

    inicializarJuego(&juego);
    mostrarNivel(juego.nivel);
    /*
    char tecla = ' ';
    bool actualizar = false;
    inicializarJuego
    mostrarNivel
    esperarInput
    tickJuego(actualizar) -> hace lo que ahora hacen los ifs de actualizar
    salirJuego(void) -> liberarMatriz, h_limpiarColor, alguna otra cosa
    */
    char tecla = ' ';
    char actualizar=1;
    while (tecla != 'q') // 'q' para salir del juego
    {
        // Actualizar solo si se logro mover al personaje
        if(actualizar)
        {
            system("cls");
            mostrarNivel(&nivel); // Muestra el mapa con el '@' adentro
            printf("\n\n\tHP: "ROJO"%d/%d "COLOR_DEFAULT" | Str: %d | G: %d",
                 jugador.hp, jugador.hpMax, juego.jugador->danio, juego.jugador->oro);
            printf("\nUsa WASD para moverte. Presiona 'q' para salir: ");
        }

        tecla = getch(); // Lee la tecla al instante sin pedir Enter

        int dx = 0, dy = 0;
        if (tecla == 'w' || tecla == 'W') dy = -1;
        if (tecla == 's' || tecla == 'S') dy = 1;
        if (tecla == 'a' || tecla == 'A') dx = -1;
        if (tecla == 'd' || tecla == 'D') dx = 1;

        if(tecla == 'i' || tecla == 'I')
        {
            int indice = seleccionarObjetoInventario(&jugador.inventario);
            if(indice != -1)
                usarObjetoInventario(&jugador, indice);
            actualizar = 1; //que actualice aunque abras el inventario y no te muevas
        }
        else
        {
            for(int i = 0; i < nivel.cant_enemigos; i++)
                localizarYMoverAJugador(&nivel, nivel.vect_enemigos + i, &jugador);

            if(dx != 0 || dy != 0) //que actualice cuando te muevas
                actualizar = moverJugador(&nivel, &jugador, dx, dy);
            else
                actualizar = 0;
        }
    }

    liberarMatriz((void**)nivel.mapa, nivel.alto);
    h_limpiarColor(); // Dario: por si se nos pasa alguno
    return 0;
}
