#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // Necesario en Windows para usar getch() sin presionar Enter
#include "../headers/mapa.h"
#include "../headers/matriz_dinamica.h"
#include "../headers/personaje.h"
#include "../headers/helpers.h"

int main()
{
    srand(time(NULL));

    Nivel nivel = inicializarNivel(80, 24, 3, 3);
    if (nivel.mapa == NULL)
    {
        system("cls");
        printf("ERROR: no se pudo crear la matriz nivel");
        return 1;
    }
    generarNivel(&nivel);

    Jugador jugador;
    inicializarJugador(&jugador);
    spawnearJugador(&nivel, &jugador); // Posiciona al '@' en la primera habitaci�n
    mostrarNivel(&nivel);
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
            // printf(TEXTO_ROJO("\nUsa WASD para moverte. Presiona 'q' para salir")); -> Demostracion texto rojo
            printf("\nUsa WASD para moverte. Presiona 'q' para salir: ");
        }

        tecla = getch(); // Lee la tecla al instante sin pedir Enter

        int dx = 0, dy = 0;
        if (tecla == 'w' || tecla == 'W') dy = -1;
        if (tecla == 's' || tecla == 'S') dy = 1;
        if (tecla == 'a' || tecla == 'A') dx = -1;
        if (tecla == 'd' || tecla == 'D') dx = 1;

        actualizar = moverJugador(&nivel, &jugador, dx, dy);
    }

    liberarMatriz((void**)nivel.mapa, nivel.alto);
    h_limpiarColor(); // Dario: por si se nos pasa alguno
    return 0;
}
