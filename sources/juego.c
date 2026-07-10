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
//#define DEBUG_BUILD

#define TECLA_ESCAPE 27
#define ANCHO_DEFAULT 80
#define ALTO_DEFAULT 24
#ifndef DEBUG_BUILD
    #define PROFUNDIDAD_MAX_DEFAULT 10
#else
    #define PROFUNDIDAD_MAX_DEFAULT 1
#endif

EstadoJuego inicializarJuego(Juego *juego)
{
    // CONFIG DEFAULT:
    static Configuracion config = {ANCHO_DEFAULT, ALTO_DEFAULT, PROFUNDIDAD_MAX_DEFAULT, 0};
    menuPrincipal(&config);
    // SI LLEGAMOS ACA, LE DIO A JUGAR
    (*juego->nivel) = inicializarNivel(&config);
    inicializarJugador(juego->jugador);

    nuevoPiso(juego);

    #ifdef DEBUG_BUILD
    //Objeto amuleto;
    //amuleto.activo = 1;
    //amuleto.x      = juego->jugador->x;
    //amuleto.y      = juego->jugador->y;
    //amuleto.tipo   = OBJ_AMULETO;
    //agregarObjetoInventario(&juego->jugador->inventario, amuleto);
    juego->jugador->danio      = 1000;
    juego->jugador->hp         = 1000;
    #endif

    return JUGANDO;
}

void nuevoPiso(Juego* juego)
{
    juego->nivel->profundidad++;

    generarNivel(juego->nivel);
    generarObjetosNivel(juego->nivel);
    generarOroNivel(juego->nivel);
    generarEscalera(juego->nivel);

    dibujarObjetosNivel(juego->nivel);
    spawnearJugador(juego->nivel, juego->jugador); // Posiciona al '@' en la primera habitacion
    determinarCantidadEnemigos(juego->nivel);
    for(int i=0; i<juego->nivel->cant_enemigos; i++)
        spawnearEnemigo(juego->nivel, juego->nivel->vect_enemigos+i);
    system("cls");
    mostrarNivel(juego->nivel);
    printf("\n\n\tHP: "ROJO"%d/%d "COLOR_DEFAULT" | Str: %d | G: %d | H: %d/%d",
            juego->jugador->hp, juego->jugador->hpMax, juego->jugador->danio, juego->jugador->oro, juego->jugador->hambre, juego->jugador->hambre_max);
    printf("\nUsa WASD para moverte. Presiona 'x' para salir: ");
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
        printf("c) MENU DE CARACTERES\n");
        printf("x) SALIR\n");

        tecla = getch();

        switch (tecla) {
            case 'a':
                return; // jugar con la configuracion actual, puede ser la default
            case 'b':
                menuConfiguracion(config);
                break;
            case 'c':
                menuCaracteres();
                break;
            default:
                break;
        }
    } while (tecla != 'x');

    exit(0); // Dario: como no reservamos memoria hasta este punto nos podemos permitir esto
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
            printf("INGRESE LA PROFUNDIDAD MAXIMA (min: %d - max: %d): ", 2, 26);
            config->profundidad_max = validarInput(2,26);
            break;
        case 'b':
            system("cls");
            printf("INGRESE EL ANCHO DEL MAPA (min: %d - max: %d): ", 20, 120);
            config->ancho_nivel = validarInput(20, 120);
            break;
        case 'c':
            system("cls");
            printf("INGRESE EL ALTO DEL MAPA (min: %d - max: %d): ", 20, 40);
            config->alto_nivel = validarInput(20, 40);
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

void menuCaracteres(void)
{
    char tecla;

    do{
        system("cls");
        printf("VARIOS\n");
        printf("'@': Personaje\n");
        printf("'.': Piso\n");
        printf("'|' o '-': Paredes\n");
        printf("'#': Pasillos\n");
        printf("'+': Puertas\n");
        printf("'\%': Escaleras, permiten bajar de piso");

        printf("\nOBJETOS\n");
        printf("')': Armas, aumenta el ataque del jugador si el ataque del arma es mayor al ataque actual.\n");
        printf("'!': Pocion, recupera el hp o aumenta el hp maximo si este ya esta lleno.\n");
        printf("':': Comida, recupera vida y sacia el hambre.\n");
        printf("'$': Monedas\n");
        printf("'" VERDE "*" COLOR_DEFAULT "': Amuleto de Yendor, obtener este amuleto es el objetivo final del juego\n"); // Puede ser que haya escrito Yandor mal xd

        printf("\nENEMIGOS\n");
        printf("'K': Kobold\n");
        printf("'L': Leprechaun\n");
        printf("'$': Mimico\n");
        printf("'N': Nymph\n");
        printf("'O': Orco\n");

        printf("\nPRESIONE X PARA VOLVER");

        tecla = getch();
    }while(tecla != 'x');
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

// Devuelve si la partida sigue o termina
EstadoJuego tickJuego(Juego* juego, char tecla)
{
    bool actualizar = false;

    int dx = 0, dy = 0;
    if (tecla == 'w' || tecla == 'W') dy = -1;
    if (tecla == 's' || tecla == 'S') dy = 1;
    if (tecla == 'a' || tecla == 'A') dx = -1;
    if (tecla == 'd' || tecla == 'D') dx = 1;

    if (tecla == 'x' || tecla == 'X') return DERROTA;

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
        juego->jugador->tick_hambre++;
        if (juego->jugador->tick_hambre == juego->jugador->proximo_tick_hambre) {
            juego->jugador->hambre++;
            juego->jugador->proximo_tick_hambre = h_numAleatorio(15, 20); // Cada 15/20 ticks, un tick de hambre
            juego->jugador->tick_hambre = 0;
        }

        if(juego->jugador->hp > 0){
            printf("\n\n\tHP: "ROJO"%d/%d "COLOR_DEFAULT" | Str: %d | G: %d | H: %d/%d",
                juego->jugador->hp,
                juego->jugador->hpMax,
                juego->jugador->danio,
                juego->jugador->oro,
                juego->jugador->hambre,
                juego->jugador->hambre_max);
            printf("\nUsa WASD para moverte. Presiona 'x' para volver al menu principal: ");
        }
        else
            return DERROTA;
    }
    return JUGANDO;
}

void ganarPartida(Juego *juego)
{
    system("cls");
    printf(VERDE "\tVICTORIA!\n\n" COLOR_DEFAULT);
    printf("ORO OBTENIDO: %dG\n", juego->jugador->oro);
    printf("ENEMIGOS ASESINADOS: %d\n", juego->jugador->enemigos_asesinados);
    printf("OBJETOS RECOGIDOS: %d\n", juego->jugador->objetos_recogidos);
    printf("PISOS COMPLETADOS: %d\n", juego->nivel->profundidad);

    printf("\nPRESIONE (x) PARA VOLVER AL MENU PRINCIPAL\n");

    char tecla;
    while (true) {
        esperarInput(&tecla);
        if (tecla == 'x')
            break;
    }
}

void salirJuego(Juego* juego)
{
    liberarMatriz((void**)juego->nivel->mapa, juego->nivel->alto);
    h_limpiarColor(); // Dario: por si se nos pasa alguno
}
