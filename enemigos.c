#include "../headers/enemigos.h"
#include "../headers/helpers.h"
#include "../headers/personaje.h"

int cantidadEnemigos(Habitacion* habitacion)
{
    int cant=0;
    int filas=habitacion->h-habitacion->y;
    int columnas=habitacion->w-habitacion->x;
    if(filas<=2 || columnas<4)
    {
        return 0;
    }
    if (columnas<=2 || filas<4)
    {
        return 0;
    }
    if(columnas>filas)
    cant=h_numAleatorio(0,columnas-2);
    else
    {
       cant=h_numAleatorio(0,filas-2);
    }


    return cant;
}

void tipoenemigo(Enemigo* enemigo)
{
    //int num=h_numAleatorio(1, 2); esto pra elegir el tipo de enemigo aliatorio pero por ahora lo dejamos desactivado para probar ambos tipos de enemigos
    int num=enemigo->tipo;
    if(num==1)
    {
        enemigo->hpMax=100;
        enemigo->hp=100;
        enemigo->atack=25;
        enemigo->tipo=1;
    }
    else
    {
        enemigo->hpMax=200;
        enemigo->hp=200;
        enemigo->atack=50;
        enemigo->tipo=2;
    }

}

void spawnearEnemigo(Nivel* nivel, Enemigo* enemigo)
{
    // Elegir una habitacion y posicion aleatoria en ella
   int secy = h_numAleatorio(0, nivel->filas - 1);
    int secx = h_numAleatorio(0, nivel->columnas - 1);
    int dy = h_numAleatorio(1, nivel->habitaciones[secy][secx].h - 2);
    int dx = h_numAleatorio(1, nivel->habitaciones[secy][secx].w - 2);

    // Colocar el enemigo
    enemigo->x = nivel->habitaciones[secy][secx].x + dx;
    enemigo->y = nivel->habitaciones[secy][secx].y + dy;
    if (nivel->mapa[enemigo->y][enemigo->x]!='.' )
    {
        //si el el enemigo spanea en el lugar del jugador volvemos a spawnear al enemigo
        spawnearEnemigo(nivel, enemigo);
        return;
    }

    if (enemigo->tipo==1)
    {
        nivel->mapa[enemigo->y][enemigo->x] ='G';/* code */
    }
    else{ nivel->mapa[enemigo->y][enemigo->x] ='E';}

}

void localizarymoverjugador(Nivel* nivel, Enemigo* enemigo, Jugador* jugador)
{
    int jugadorx=jugador->x;
    int jugadory=jugador->y;
    int enemigosx=enemigo->x;
    int  enemigosy= enemigo->y;
    int calx=jugadorx-enemigosx;
    int caly=jugadory-enemigosy;
    if((calx>3 || calx<-3) || (caly>3 || caly<-3))
    {
        return;
    }
    if((calx>=-1 && calx<=1) &&(caly>=-1 && caly<=1) )
    {
        atacarajugador(enemigo, jugador);
            puts("ataco\n");

    }
else
    {
           if(caly>1)
            {
                enemigosy++;
            }
            if(caly<-1)
            {
                 enemigosy--;
            }
            if(calx>1)
            {
                enemigosx++;
            }
            if(calx<-1)
            {
                enemigosx--;
            }

    }
    if(nivel->mapa[enemigosy][enemigosx]!='.'){
        return;
        }

    nivel->mapa[enemigo->y][enemigo->x]='.';
    if(enemigo->tipo==1)
    {
        nivel->mapa[enemigosy][enemigosx] ='G';/* code */
    }
    else
    { nivel->mapa[enemigosy][enemigosx] ='E';}
    enemigo->x=enemigosx;
    enemigo->y=enemigosy;


}

void atacarajugador(Enemigo* enemigo, Jugador* jugador)
{
    jugador->hp -=enemigo->atack;
}

void eleminarEnemigo(Nivel* nivel, Enemigo* enemigo)
{
    nivel->mapa[enemigo->y][enemigo->x] = '.';
}
