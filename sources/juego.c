#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#include "../headers/juego.h"
#include "../headers/mapa.h"
#include "../headers/personaje.h"
#include "../headers/enemigos.h"
#include "../headers/matriz_dinamica.h"
#include "../headers/helpers.h"

// DARIO: COMENTAR ESTA LINEA SI NO VAN A DEBUGGEAR
#define DEBUG_BUILD

#define TECLA_ESCAPE 27
#define ANCHO_DEFAULT 80
#define ALTO_DEFAULT 24
#ifndef DEBUG_BUILD
    #define PROFUNDIDAD_MAX_DEFAULT 10
#else
    #define PROFUNDIDAD_MAX_DEFAULT 1
#endif

bool inicializarJuego(Juego *juego)
{
    Configuracion config = {0};
    // CONFIG DEFAULT:
    config.ancho_nivel = ANCHO_DEFAULT;
    config.alto_nivel = ALTO_DEFAULT;
    config.enemigos_reducidos = 0; // FALSO
    config.profundidad_max = PROFUNDIDAD_MAX_DEFAULT;
    menuPrincipal(&config);
    // SI LLEGAMOS ACA, LE DIO A JUGAR
    (*juego->nivel) = inicializarNivel(&config);
    inicializarJugador(juego->jugador);
    generarNivel(juego->nivel);
    generarObjetosNivel(juego->nivel);
    generarOroNivel(juego->nivel);

    #ifdef DEBUG_BUILD
    Objeto amuleto;
    amuleto.activo = 1;
    amuleto.x      = juego->jugador->x;
    amuleto.y      = juego->jugador->y;
    amuleto.tipo   = OBJ_AMULETO;
    agregarObjetoInventario(&juego->jugador->inventario, amuleto);
    #endif

    dibujarObjetosNivel(juego->nivel);
    spawnearJugador(juego->nivel, juego->jugador); // Posiciona al '@' en la primera habitacion
    determinarCantidadEnemigos(juego->nivel);
    for(int i=0; i<juego->nivel->cant_enemigos; i++)
        spawnearEnemigo(juego->nivel, juego->nivel->vect_enemigos+i);
    system("cls");
    mostrarNivel(juego->nivel);
    printf("\n\n\tHP: "ROJO"%d/%d "COLOR_DEFAULT" | Str: %d | G: %d",
            juego->jugador->hp, juego->jugador->hpMax, juego->jugador->danio, juego->jugador->oro);
    printf("\nUsa WASD para moverte. Presiona 'x' para salir: ");
    return true;
}

void menuPrincipal(Configuracion *config)
{
    char tecla;
    // Se tiene que poder modificar la profundidad maxima, la cantidad de enemigos (reducido/normal), y ancho alto inicial de mapa
    do {
        system("cls");
        printf( AZUL "\t\tBalatro Rogue\n\n" COLOR_DEFAULT);
        printf("a) JUGAR\n");
        printf("b) CONFIGURACION\n");
        printf("x) SALIR\n");

        tecla = getch();

        switch (tecla) {
            case 'a':
                return; // jugar con la configuracion actual, puede ser la default
            case 'b':
                menuConfiguracion(config);
                break;
            default:
                break;
        }
    } while (tecla != 'x');

    exit(1); // Dario: como no reservamos memoria hasta este punto nos podemos permitir esto
}

void menuConfiguracion(Configuracion *config)
{
    char tecla;

    do {
        system("cls");
        printf( AZUL "\t\tCONFIGURACION\n\n" COLOR_DEFAULT);
        printf("a) PROFUNDIDAD MAXIMA : %d\n", config->profundidad_max);
        printf("b) ANCHO DEL MAPA : %d\n", config->ancho_nivel);
        printf("c) ALTO DEL MAPA : %d\n", config->alto_nivel);
        printf("d) ENEMIGOS : %s\n", config->enemigos_reducidos ? "REDUCIDO" : "NORMAL");
        printf("x) VOLVER AL MENU PRINCIPAL\n");

        tecla = getch();

        switch (tecla) {
        case 'a':
            system("cls");
            printf("INGRESE LA PROFUNDIDAD MAXIMA (min: %d - max: %d): ", 1, 20);
            config->profundidad_max = validarInput(1,20);
            break;
        case 'b':
            system("cls");
            printf("INGRESE EL ANCHO DEL MAPA (min: %d - max: %d): ", 30, 120);
            config->ancho_nivel = validarInput(30, 120);
            break;
        case 'c':
            system("cls");
            printf("INGRESE EL ALTO DEL MAPA (min: %d - max: %d): ", 10, 40);
            config->alto_nivel = validarInput(10, 40);
            break;
        case 'd':
            system("cls");
            printf("INGRESE SI DESEA ENEMIGOS REDUCIDOS (reducido: 1 - normal: 0): ");
            config->enemigos_reducidos = validarInput(0, 1);
            break;
        default:
            break;
        }
    } while (tecla != 'x');
}

int validarInput(int rango_min, int rango_max)
{
    int input;
    scanf("%d", &input);
    while (input < rango_min || input > rango_max) {
        system("cls");
        printf("VALOR INVALIDO, INGRESE NUEVAMENTE (min: %d - max: %d): ", rango_min, rango_max);
        scanf("%d", &input);
    }

    return input;
}

void esperarInput(char* tecla)
{
    *tecla = getch(); // Lee la tecla al instante sin pedir Enter
}

bool tickJuego(Juego* juego, char tecla)
{
    bool actualizar = false;

    int dx = 0, dy = 0;
    if (tecla == 'w' || tecla == 'W') dy = -1;
    if (tecla == 's' || tecla == 'S') dy = 1;
    if (tecla == 'a' || tecla == 'A') dx = -1;
    if (tecla == 'd' || tecla == 'D') dx = 1;

    if (tecla == 'x' || tecla == 'X') return false;

    if(tecla == 'i' || tecla == 'I')
    {
        int indice = seleccionarObjetoInventario(&juego->jugador->inventario);
        if(indice != -1)
            usarObjetoInventario(juego->jugador, indice);
        actualizar = true; //que actualice aunque abras el inventario y no te muevas
    }
    else
    {
        for(int i = 0; i < juego->nivel->cant_enemigos; i++)
            actualizar |= localizarYMoverAJugador(juego->nivel, juego->nivel->vect_enemigos + i, juego->jugador);

        if(dx != 0 || dy != 0) //que actualice cuando te muevas
            actualizar |= moverJugador(juego->nivel, juego->jugador, dx, dy);
    }

    // Actualizar solo si se logro mover al personaje
    if(actualizar)
    {
        system("cls");
        mostrarNivel(juego->nivel); // Muestra el mapa con el '@' adentro

        if(juego->jugador->hp > 0){
            printf("\n\n\tHP: "ROJO"%d/%d "COLOR_DEFAULT" | Str: %d | G: %d",
                juego->jugador->hp, juego->jugador->hpMax, juego->jugador->danio, juego->jugador->oro);
            printf("\nUsa WASD para moverte. Presiona 'x' para volver al menu principal: ");
        }
        else
            return false;
    }
    return true;
}

void salirJuego(Juego* juego)
{
    liberarMatriz((void**)juego->nivel->mapa, juego->nivel->alto);
    h_limpiarColor(); // Dario: por si se nos pasa alguno
}
