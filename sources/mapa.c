#include "../headers/mapa.h"
#include "../headers/matriz_dinamica.h"
#include "../headers/helpers.h"
#include <stdio.h>

void inicializarMapa(Nivel* nivel)
{
    for (int y = 0; y < nivel->alto; y++) {
        for (int x = 0; x < nivel->ancho; x++) {
            nivel->mapa[y][x] = ' ';
        }
    }
}

void generarNivel(Nivel* nivel)
{
    inicializarMapa(nivel);
    Habitacion** habs = (Habitacion**)CrearMatriz(nivel->filas, nivel->columnas, sizeof(Habitacion));

    int sectorW = nivel->ancho / nivel->columnas;
    int sectorH = nivel->alto / nivel->filas;

    for (int f = 0; f < nivel->filas; f++) {
        for (int c = 0; c < nivel->columnas; c++) {
            Habitacion hab;

            hab.sectorX = c;
            hab.sectorY = f;

            // minimo de 4 para una habitacin 2x2
            // maximo de sectorW/H - 2 para que la habitacion entre en el sector sin que este pegado en el borde
            hab.w = NumeroAleatorio(4, sectorW - 2);
            hab.h = NumeroAleatorio(4, sectorH - 2);

            // x e y en posiciones aleatorias pero dejando espacio para los pasillos
            hab.x = (c * sectorW) + NumeroAleatorio(1, sectorW - hab.w - 1);
            hab.y = (f * sectorH) + NumeroAleatorio(1, sectorH - hab.h - 1);

            generarHabitacion(nivel, &hab);
            habs[f][c] = hab;
        }
    }
    nivel->habitaciones = habs;

    conectarHabitaciones(nivel);
}

void MostrarNivel(Nivel* nivel)
{
    for (int y = 0; y < nivel->alto; y++) {
        if(y) printf("\n");
        for (int x = 0; x < nivel->ancho; x++) {
            printf("%c", nivel->mapa[y][x]);
        }
    }
}

void generarHabitacion(Nivel* nivel, Habitacion* h)
{
    for (int y = h->y; y < (h->y + h->h); y++) {
        for (int x = h->x; x < (h->x + h->w); x++) {
            if(y==h->y || y==h->y + h->h - 1)
                nivel->mapa[y][x] = '-'; // Poner las paredes horizontales
            else if (x==h->x || x==h->x + h->w - 1)
                nivel->mapa[y][x] = '|'; // Poner las paredes verticales
            else
                nivel->mapa[y][x] = '.'; // Poner piso
        }
    }
}

void conectarHabitaciones(Nivel* nivel)
{
    // Matriz de sectores visitados
    int** visitado = malloc(sizeof(int*)*nivel->filas);
    for(int y = 0; y < nivel->filas; y++)
        visitado[y] = calloc( nivel->columnas, sizeof(int));

    int inicioX = NumeroAleatorio(0, nivel->columnas - 1);
    int inicioY = NumeroAleatorio(0, nivel->filas - 1);

    // Iniciar el algoritmo de conexion
    dfsConectar(nivel, inicioX, inicioY, visitado);

    for(int y = 0; y < nivel->filas; y++)
        free(visitado[y]);
    free(visitado);
}

void dfsConectar(Nivel* nivel, int x, int y, int** visitado)
{
    // Marcar el sector actual como visitado
    static unsigned int total=1;
    visitado[y][x] = 1;

    while(total < nivel->filas*nivel->columnas) // Mientras no se hayan visitado todos los sectores
    {
        // Guardar a que lugares te podes mover sin salirte de los limites y sin repetir un sector ya visitado
        int posibles[4][2];
        int cantidad = 0;

        // arriba
        if(y > 0 && !visitado[y - 1][x])
        {
            posibles[cantidad][0] = x;
            posibles[cantidad][1] = y - 1;
            cantidad++;
        }

        // derecha
        if(x < nivel->columnas - 1 && !visitado[y][x + 1])
        {
            posibles[cantidad][0] = x + 1;
            posibles[cantidad][1] = y;
            cantidad++;
        }

        // abajo
        if(y < nivel->filas - 1 && !visitado[y + 1][x])
        {
            posibles[cantidad][0] = x;
            posibles[cantidad][1] = y + 1;
            cantidad++;
        }

        // izquierda
        if(x > 0 && !visitado[y][x - 1])
        {
            posibles[cantidad][0] = x - 1;
            posibles[cantidad][1] = y;
            cantidad++;
        }

        // no quedan vecinos libres
        if(cantidad == 0)
            return;

        int elegido = NumeroAleatorio(0, cantidad - 1);

        int nx = posibles[elegido][0];
        int ny = posibles[elegido][1];

        generarPasillos(nivel, &nivel->habitaciones[y][x], &nivel->habitaciones[ny][nx]);

        // Repetir el algortimo con el sector seleccionado
        dfsConectar(nivel, nx, ny, visitado);
    }
    return;
}

// Solo funciona si las habitaciones estan en sectores adyacentes
void generarPasillos(Nivel* nivel, Habitacion* h1, Habitacion* h2)
{
    int horizontal = (h1->sectorX != h2->sectorX) ? 1 : 0;
    int p1x, p1y, p2x, p2y, pMedio;

    // Marcos: Seleccionar 2 puntos en las pardes mas cercanas de las habitaciones a unir
    if(horizontal)
    {
        if(h1->sectorX < h2->sectorX)
        {
            p1x = h1->x + h1->w - 1;
            p1y = NumeroAleatorio(h1->y + 1, h1->y + h1->h - 2);
            p2x = h2->x;
            p2y = NumeroAleatorio(h2->y + 1, h2->y + h2->h - 2);
        }
        else
        {
            p1x = h1->x;
            p1y = NumeroAleatorio(h1->y + 1, h1->y + h1->h - 2);
            p2x = h2->x + h2->w - 1;
            p2y = NumeroAleatorio(h2->y + 1, h2->y + h2->h - 2);
        }
        pMedio = (p1x + p2x)/2;
    }
    else
    {
        if(h1->sectorY < h2->sectorY)
        {
            p1x = NumeroAleatorio(h1->x + 1, h1->x + h1->w - 2);
            p1y = h1->y + h1->h - 1;
            p2x = NumeroAleatorio(h2->x + 1, h2->x + h2->w - 2);
            p2y = h2->y;
        }
        else
        {
            p1x = NumeroAleatorio(h1->x + 1, h1->x + h1->w - 2);
            p1y = h1->y;
            p2x = NumeroAleatorio(h2->x + 1, h2->x + h2->w - 2);
            p2y = h2->y + h2->h - 1;
        }
        pMedio = (p1y + p2y)/2;
    }

    nivel->mapa[p1y][p1x] = '+';
    nivel->mapa[p2y][p2x] = '+';

    // Marcos: Hacer un camino tipo 'Z' dependiendo de la posicion de las habitaciones
    if(horizontal)
    {
        while(p1x != pMedio)
        {
            if(nivel->mapa[p1y][p1x] == ' ')
                nivel->mapa[p1y][p1x] = '#';
            p1x += (p1x < pMedio) ? 1 : -1;
        }

        while(p1y != p2y)
        {
            if(nivel->mapa[p1y][p1x] == ' ')
                nivel->mapa[p1y][p1x] = '#';
            p1y += (p1y < p2y) ? 1 : -1;
        }

        while(p1x != p2x)
        {
            if(nivel->mapa[p1y][p1x] == ' ')
                nivel->mapa[p1y][p1x] = '#';
            p1x += (p1x < p2x) ? 1 : -1;
        }
    }
    else
    {
        while(p1y != pMedio)
        {
            if(nivel->mapa[p1y][p1x] == ' ')
                nivel->mapa[p1y][p1x] = '#';
            p1y += (p1y < pMedio) ? 1 : -1;
        }

        while(p1x != p2x)
        {
            if(nivel->mapa[p1y][p1x] == ' ')
                nivel->mapa[p1y][p1x] = '#';
            p1x += (p1x < p2x) ? 1 : -1;
        }

        while(p1y != p2y)
        {
            if(nivel->mapa[p1y][p1x] == ' ')
                nivel->mapa[p1y][p1x] = '#';
            p1y += (p1y < p2y) ? 1 : -1;
        }
    }
}
