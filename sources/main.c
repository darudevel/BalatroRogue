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

    Nivel nivel;
    nivel.ancho = 80;
    nivel.alto = 24;
    nivel.filas = 3;
    nivel.columnas = 3;
    //nivel.ancho >= 6*nivel.columnas && nivel.alto >= 6*nivel.filas sino se rompe el programa.
    nivel.mapa = (char**)CrearMatriz(nivel.alto, nivel.ancho, sizeof(char));
    if (nivel.mapa == NULL)
    {
        printf("No se pudo crear matriz");
        return 1;
    }
    generarNivel(&nivel);

    Jugador jugador;
    inicializarJugador(&jugador);
    spawnearJugador(&nivel, &jugador); // Posiciona al '@' en la primera habitación

    char tecla = ' ';
    char actualizar=1;
    while (tecla != 'q') // 'q' para salir del juego
    {
        // Actualizar solo si se logro mover al personaje
        if(actualizar){
            system("cls");
            MostrarNivel(&nivel); // Muestra el mapa con el '@' adentro
            printf("\n\nHP: %d/%d | Pos: (%d, %d)", jugador.hp, jugador.hpMax, jugador.x, jugador.y);
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

    LiberarMatriz((void**)nivel.mapa, nivel.alto);
    return 0;
}
