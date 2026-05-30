#include "../headers/mapa.h"
#include "../headers/personaje.h"
#include "../headers/helpers.h"
#include "../headers/enemigos.h"

void spawnearJugador(Nivel* nivel, Jugador* jugador)
{
    // Elegir una habitacion y posicion aleatoria en ella
    int secy = h_numAleatorio(0, nivel->filas - 1);
    int secx = h_numAleatorio(0, nivel->columnas - 1);
    int dy = h_numAleatorio(1, nivel->habitaciones[secy][secx].h - 2);
    int dx = h_numAleatorio(1, nivel->habitaciones[secy][secx].w - 2);

    // Colocar el personaje
    jugador->x = nivel->habitaciones[secy][secx].x + dx;
    jugador->y = nivel->habitaciones[secy][secx].y + dy;
    nivel->mapa[jugador->y][jugador->x] = '@';
}

void inicializarJugador(Jugador* jugador)
{
    jugador->hp = 100;
    jugador->hpMax = 100;
    jugador->oro = 0;
    jugador->danio = 40;
    jugador->escalera = false;
    inicializarInventario(&jugador->inventario);
}

bool moverJugador(Nivel* nivel, Jugador* jugador, int dx, int dy)
{
    int nx = jugador->x + dx;
    int ny = jugador->y + dy;

    //Evitamos desbordamientos fisicos de la matriz (limites del mapa)
    if (nx < 0 || nx >= nivel->ancho || ny < 0 || ny >= nivel->alto)
    {
        return false; // Movimiento invalido, no hace nada el jugador ya que no podra salir de los limites
    }
    char destino = nivel->mapa[ny][nx];
    // se movio hacia un enemigo, entonces, atacar
    int pos = buscarEnemigoEnPosicion(nivel, nx, ny);
    if(pos != -1)
    {
        atacaraenemigo(nivel, nivel->vect_enemigos + pos, jugador);
        return true;
    }
    else if (destino == '%'){
        jugador->escalera = true;
        return false;
    }
    //Comprobamos si el casillero de destino es transitable
    else if (destino == '.'     // Piso
        || destino == '#'  // Pasillo
        || destino == '+'  // Puerta
        || destino == '*'  // Amuleto
        || destino == '$'  // Oro
        || destino == '!'  // Pocion
        || destino == ':'  // Comida
        || destino == ')') // Arma
    {
        // EMA: Mas o menos se podria explicar que guardamos el caracter donde esta parado el jugador.
        // Como el jugador pisa cosas, al salir de un casillero debemos restaurar lo que habia previamente
        // restauramos el casillero anterior basandonos en que era originalmente.
        // Para evitar borrar pasillos ('#') o puertas ('+') al caminar sobre ellos,
        // podemos declarar una variable estatica en C que recuerde que caracter "tapo" el jugador:
        static char bajoElJugador = '.';

        // Restauramos el casillero viejo con lo que habia abajo antes de que el '@' se parara alli
        nivel->mapa[jugador->y][jugador->x] = bajoElJugador;

        //Se llama antes a esta funcion para que cuando pise el objeto, no se restaure donde estaba anteriormente, sino que desaparezca
        recogerObjeto(nivel, jugador, nx, ny);

        // Guardamos lo que hay en el NUEVO casillero antes de pararnos
        bajoElJugador = nivel->mapa[ny][nx];

        // Movemos al jugador a las nuevas coordenadas
        jugador->x = nx;
        jugador->y = ny;

        // Dibujamos al jugador en su nueva posicion en el mapa
        nivel->mapa[ny][nx] = '@';

        return true; // Se logro mover al jugador
    }
    return false;
}

int atacaraenemigo(Nivel* nivel, Enemigo* enemigo, Jugador* jugador)
{
    enemigo->hp -= jugador->danio;

    if(enemigo->hp <= 0){
        eleminarEnemigo(nivel, enemigo);
        return 1;
    }

        return 0;
}
