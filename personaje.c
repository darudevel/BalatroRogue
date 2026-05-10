#include "headers/personaje.h"

#include <stdio.h>

void spawnearJugador(Nivel nivel, Jugador* jugador)
{
    // Buscamos de forma secuencial la primera habitación para posicionar al jugador
    for (int y = 0; y < nivel.alto; y++)
    {
        for (int x = 0; x < nivel.ancho; x++)
        {
            // Buscamos un casillero que sea suelo de habitación ('.')
            if (nivel.mapa[y][x] == '.')
            {
                jugador->x = x;
                jugador->y = y;
                nivel.mapa[y][x] = '@'; // Colocamos el caracter del héroe en el mapa

                // Inicializamos sus estadísticas básicas
                jugador->hpMax = 100;
                jugador->hp = 100;
                return; // Ya encontramos lugar, salimos de la función
            }
        }
    }
}

void moverJugador(Nivel nivel, Jugador* jugador, int dx, int dy)
{
    int nx = jugador->x + dx;
    int ny = jugador->y + dy;

    //Evitamos desbordamientos físicos de la matriz (límites del mapa)
    if (nx < 0 || nx >= nivel.ancho || ny < 0 || ny >= nivel.alto)
    {
        return; // Movimiento inválido, no hace nada el jugador ya que no podra salir de los limites
    }
    //Comprobamos si el casillero de destino es transitable
    char destino = nivel.mapa[ny][nx];
    if (destino == '.' || destino == '#' || destino == '+') // Por ahora, asumimos que se mueve sobre piso '.','+' o pasillos '#' comunes.
    {
        // EMA: Mas o menos se podria explicar que guardamos el caracter donde está parado el jugador.
        // Como el jugador pisa cosas, al salir de un casillero debemos restaurar lo que había previamente
        // restauramos el casillero anterior basándonos en qué era originalmente.
        // Para evitar borrar pasillos ('#') o puertas ('+') al caminar sobre ellos,
        // podemos declarar una variable estática en C que recuerde qué caracter "tapó" el jugador:
        static char bajoElJugador = '.';

        // Restauramos el casillero viejo con lo que había abajo antes de que el '@' se parara allí
        nivel.mapa[jugador->y][jugador->x] = bajoElJugador;

        // Guardamos lo que hay en el NUEVO casillero antes de pararnos
        bajoElJugador = nivel.mapa[ny][nx];

        // Movemos al jugador a las nuevas coordenadas
        jugador->x = nx;
        jugador->y = ny;

        // Dibujamos al jugador en su nueva posición en el mapa
        nivel.mapa[ny][nx] = '@';
    }
}
