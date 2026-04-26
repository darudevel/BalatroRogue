#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#define ANCHO_INICIAL 60
#define ALTO_INICIAL 60

// TODO: ver que numero queda bien
#define FILAS 3
#define COLS 3

typedef struct {
    int x, y, w, h;
    int centroX, centroY;
} Habitacion;

// daru: posiblemente cambiemos todas estas firmas porque todavia no hicimos consenso de como hacer la estructura de juego y todo eso jeee
void inicializarMapa(char **mapa);
void generarNivel(char **mapa);
void generarHabitacion(char **mapa, Habitacion h);
void conectarHabitaciones(char **mapa, Habitacion h1, Habitacion h2);

#endif // MAPA_H_INCLUDED
