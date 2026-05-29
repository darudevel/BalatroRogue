#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

// Para romper la dependencia circular
typedef struct Nivel Nivel;
typedef struct Jugador Jugador;

typedef enum {
    OBJ_ORO = 1,
    OBJ_POCION,
    OBJ_COMIDA,
    OBJ_ARMA,
    OBJ_AMULETO
} TipoObjeto;

#define CAPACIDAD_INVENTARIO 15 //esto se puede modificar luego
#define MAX_OBJETOS_NIVEL 9
#define MAX_ORO_NIVEL 7

typedef struct{
    int x; //Posiciones en el mapa
    int y;
    TipoObjeto tipo;
    char representacion;
    int valor; //depende del tipo de Objeto (50 monedas, pocion cura 20 hp)
    int activo; //si fue recogido o no
}Objeto;

typedef struct{
    Objeto objetos[CAPACIDAD_INVENTARIO];
    int cantidad;
}Inventario;

void inicializarInventario(Inventario* inventario);
Objeto crearObjeto(TipoObjeto tipo, int x, int y, int profundidad_actual);
int agregarObjetoInventario(Inventario* inventario, Objeto objeto);
int seleccionarObjetoInventario(Inventario* inventario);
void generarObjetosNivel(Nivel* nivel); //Trabajar el oro y los objetos como cosas diferentes pq el limite de objetos en el Rogue original era 9
void generarOroNivel(Nivel* nivel);     //Pero el oro no tenia limite (elegi limite 7 por definir algun valor)
void dibujarObjetosNivel(Nivel* nivel);
int buscarObjetoEnPosicion(Nivel* nivel, int x, int y);
int buscarOroEnPosicion(Nivel* nivel, int x, int y);
void recogerObjeto(Nivel* nivel, Jugador* jugador, int x, int y);
void eliminarObjetoInventario(Inventario* inventario, int indice);
int usarObjetoInventario(Jugador* jugador, int indice);
#endif // OBJETOS_H_INCLUDED
