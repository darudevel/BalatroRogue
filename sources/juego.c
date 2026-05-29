#include "../headers/juego.h"
#include "../headers/mapa.h"
#include "../headers/personaje.h"

void inicializarJuego(Juego *juego)
{
    generarNivel(juego->nivel);
    generarObjetosNivel(juego->nivel);
    generarOroNivel(juego->nivel);
    dibujarObjetosNivel(juego->nivel);
    inicializarJugador(juego->jugador);
    spawnearJugador(juego->nivel, juego->jugador); // Posiciona al '@' en la primera habitaci�n
}