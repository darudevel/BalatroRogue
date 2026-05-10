#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/mapa.h"
#include "headers/matriz_dinamica.h"
#include "headers/personaje.h"

#include <conio.h> // Necesario en Windows para usar getch() sin presionar Enter

int main()
{
    Nivel nivel;
    nivel.ancho = 80;
    nivel.alto = 24;
    nivel.filas = 3;
    nivel.columnas = 3;
//nivel.ancho >= 6*nivel.columnas && nivel.alto >= 6*nivel.filas sino se rompe el programa.
    nivel.mapa = (char**)crearMatriz(nivel.alto, nivel.ancho, sizeof(char));
    if (nivel.mapa == NULL)
    {
        printf("No se pudo crear matriz");
        return 1;
    }
    generarNivel(nivel);

    Jugador jugador;
    spawnearJugador(nivel, &jugador); // Posiciona al '@' en la primera habitación

    char tecla = ' ';
    while (tecla != 'q') // 'q' para salir del juego
    {
        system("cls");
        MostrarMatriz(nivel); // Muestra el mapa con el '@' adentro
        printf("\n\nHP: %d/%d | Pos: (%d, %d)", jugador.hp, jugador.hpMax, jugador.x, jugador.y);
        printf("\nUsa WASD para moverte. Presiona 'q' para salir: ");

        tecla = getch(); // Lee la tecla al instante sin pedir Enter

        int dx = 0, dy = 0;
        if (tecla == 'w' || tecla == 'W') dy = -1;
        if (tecla == 's' || tecla == 'S') dy = 1;
        if (tecla == 'a' || tecla == 'A') dx = -1;
        if (tecla == 'd' || tecla == 'D') dx = 1;

        moverJugador(nivel, &jugador, dx, dy);
    }

    destruirMatriz((void**)nivel.mapa, nivel.alto);
    return 0;

    return 0;
}
