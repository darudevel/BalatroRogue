#include <stdio.h>
#include <stdlib.h>
#include "../headers/enemigos.h"
#include "../headers/helpers.h"
#include "../headers/mapa.h"
#include "../headers/personaje.h"

void determinarCantidadEnemigos(Nivel* nivel)
{
    nivel->cant_enemigos = nivel->profundidad +  nivel->profundidad * h_numAleatorio(1, 3);

    nivel->vect_enemigos = (Enemigo*)malloc(sizeof(Enemigo)*nivel->cant_enemigos);
}

void determinarTipoEnemigo(Enemigo* enemigo)
{
    enemigo->tipo = h_numAleatorio(KOBOLD, ORC);
    switch (enemigo->tipo) {
    case KOBOLD:
        enemigo->hpMax  = 100;
        enemigo->hp     = 100;
        enemigo->attack = 15;
        enemigo->representacion = 'K';
        break;
    case LEPRECHAUN:
        enemigo->hpMax  = 120;
        enemigo->hp     = 120;
        enemigo->attack = 20;
        enemigo->representacion = 'L';
        break;
    case MIMIC:
        enemigo->hpMax  = 150;
        enemigo->hp     = 150;
        enemigo->attack = 10;
        enemigo->representacion = 'M'; 
        break;
    case NYMPH:
        enemigo->hpMax  = 200;
        enemigo->hp     = 200;
        enemigo->attack = 25;
        enemigo->representacion = 'N';
        break;
    case ORC:
        enemigo->hpMax  = 250;
        enemigo->hp     = 250;
        enemigo->attack = 30;
        enemigo->representacion = 'O';
        break;
    default:
        printf("no se como hiciste para llegar aca!\n");
        break;
    }
}

void spawnearEnemigo(Nivel* nivel, Enemigo* enemigo)
{
    determinarTipoEnemigo(enemigo);

    do{
        // Elegir una habitacion y posicion aleatoria en ella
        int secy = h_numAleatorio(0, nivel->filas - 1);
        int secx = h_numAleatorio(0, nivel->columnas - 1);
        int dy = h_numAleatorio(1, nivel->habitaciones[secy][secx].h - 2);
        int dx = h_numAleatorio(1, nivel->habitaciones[secy][secx].w - 2);

        // Colocar el enemigo
        enemigo->x = nivel->habitaciones[secy][secx].x + dx;
        enemigo->y = nivel->habitaciones[secy][secx].y + dy;
        //si el el enemigo spawnea en el lugar del jugador volvemos a spawnear al enemigo
    } while(nivel->mapa[enemigo->y][enemigo->x] != '.');

     nivel->mapa[enemigo->y][enemigo->x] = enemigo->representacion;
}

bool localizarYMoverAJugador(Nivel* nivel, Enemigo* enemigo, Jugador* jugador)
{
    int jugador_x    = jugador->x;
    int jugador_y    = jugador->y;
    int enemigos_x   = enemigo->x;
    int enemigos_y   = enemigo->y;
    int distancia_x  = jugador_x-enemigos_x;
    int distancia_y  = jugador_y-enemigos_y;

    if ( (ABS(distancia_x) >= RANGO_VISION) || ABS(distancia_y) >= RANGO_VISION) {
        return false; // Dario: si no esta en el campo de vision del enemigo, no hacemos nada
    }
    if ( ((distancia_x == 0) && (ABS(distancia_y) == 1)) || ((ABS(distancia_x) == 1) && (distancia_y == 0))) {
        atacarAJugador(enemigo, jugador);
        // TODO: mover el cursor arriba a la izquierda del todo para mostrar estos logs
        printf("Enemigo tipo %c ataco al jugador por %d danio\n", enemigo->representacion, enemigo->attack);
    }
    else {
        enemigos_y += (distancia_y > 1) ? 1 : (distancia_y < -1) ? -1 : 0;
        enemigos_x += (distancia_x > 1) ? 1 : (distancia_x < -1) ? -1 : 0;

        if(nivel->mapa[enemigos_y][enemigos_x]!='.')
            return false;
        // si llegamos hasta aca, mover al enemigo
        nivel->mapa[enemigo->y][enemigo->x]='.';
        nivel->mapa[enemigos_y][enemigos_x] = enemigo->representacion;

        enemigo->x = enemigos_x;
        enemigo->y = enemigos_y;
    }
    return true;
}

void atacarAJugador(Enemigo* enemigo, Jugador* jugador)
{
    jugador->hp -= enemigo->attack;
}

void eleminarEnemigo(Nivel* nivel, Enemigo* enemigo)
{
    nivel->mapa[enemigo->y][enemigo->x] = '.';

    int pos = buscarEnemigoEnPosicion(nivel, enemigo->x, enemigo->y);
    if(pos != -1){
        for(pos++; pos < nivel->cant_enemigos; pos++){
            nivel->vect_enemigos[pos-1] = nivel->vect_enemigos[pos];
        }
        nivel->cant_enemigos--;
        
    }

    if(!nivel->cant_enemigos)
        free(nivel->vect_enemigos);
}

int buscarEnemigoEnPosicion(Nivel* nivel, int x, int y)
{
    for(int i = 0; i < nivel->cant_enemigos; i++)
    {
        if(nivel->vect_enemigos[i].x == x && nivel->vect_enemigos[i].y == y)
            return i;
    }

    return -1;
}
