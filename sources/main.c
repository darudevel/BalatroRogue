#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    
    Jugador jugador;
    Nivel   nivel = inicializarNivel(80, 24, 3, 3);
    Juego   juego;
    
    juego.nivel   = &nivel;
    juego.jugador = &jugador;

    inicializarJuego(&juego);
    mostrarNivel(juego.nivel);
    char tecla = ' ';
    char actualizar=1;
    while (tecla != 'q') // 'q' para salir del juego
    {
        // Actualizar solo si se logro mover al personaje
        if(actualizar)
        {
            system("cls");
            mostrarNivel(&nivel); // Muestra el mapa con el '@' adentro
            printf("\n\nHP: "ROJO"%d/%d "COLOR_DEFAULT" | Pos: (%d, %d)", jugador.hp, jugador.hpMax, jugador.x, jugador.y);
            printf("\nUsa WASD para moverte. Presiona 'q' para salir: ");
        }

        tecla = getch(); // Lee la tecla al instante sin pedir Enter

        int dx = 0, dy = 0;
        if (tecla == 'w' || tecla == 'W') dy = -1;
        if (tecla == 's' || tecla == 'S') dy = 1;
        if (tecla == 'a' || tecla == 'A') dx = -1;
        if (tecla == 'd' || tecla == 'D') dx = 1;

        if (tecla == 'i' || tecla == 'I')
        {
            int indice = seleccionarObjetoInventario(&jugador.inventario);
            if(indice != -1)
                usarObjetoInventario(&jugador, indice);
            actualizar = 1; //que actualice aunque abras el inventario y no te muevas
        }
        else if(dx != 0 || dy != 0) //que actualice cuando te muevas
        {
            actualizar = moverJugador(&nivel, &jugador, dx, dy);
        }
        else
        {
            actualizar = 0;
        }
    }

    liberarMatriz((void**)nivel.mapa, nivel.alto);
    h_limpiarColor(); // Dario: por si se nos pasa alguno
    return 0;
}
