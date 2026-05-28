#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "../headers/objetos.h"
#include "../headers/mapa.h"
#include "../headers/personaje.h"
#include "../headers/helpers.h"
void inicializarInventario(Inventario* inventario)
{
    inventario->cantidad = 0;
}

Objeto crearObjeto(int tipo, int x, int y)
{
    Objeto objeto;

    objeto.x = x;
    objeto.y = y;
    objeto.tipo = tipo;
    objeto.activo = 1;

    //Dependen del objeto
    switch(tipo)
    {
        case OBJ_ORO:
            objeto.representacion = '*';
            objeto.valor= h_numAleatorio(5,50); //Originalmente la cuenta q hacia del oro era
            break;                               //random(50 + 10 * nivel) + 2, osea q iba dependiendo del nivel
                                                // se puede modificar una vez establecido un valor en los niveles
        case OBJ_POCION:
            objeto.representacion = '!';
            objeto.valor = 20; //Cura 20 de vida (si la vida esta al Maximo, aumenta la vidaMax). Puede ser modificado por otro valor
            break;

        case OBJ_COMIDA:
            objeto.representacion = ':';
            objeto.valor = 15; //Cura 15 de vida. Puede ser modificado por otro valor
            break;

        case OBJ_ARMA:
            objeto.representacion = ')';
            objeto.valor = 5; //5 de daño aumentado
            break;

        case OBJ_AMULETO:
            objeto.representacion = ',';
            objeto.valor = 0; //Tengo entendido que con eso ganas el juego, tendriamos q ponerlo en el ultimo Nivel y q solo apareciera
            break;            //una vez como condicion de victoria

        default:
            objeto.representacion = '?';
            objeto.valor = 0;
            objeto.activo = 0;
            break;
    }

    return objeto;
}

int agregarObjetoInventario(Inventario* inventario, Objeto objeto)
{
    if(inventario->cantidad >= CAPACIDAD_INVENTARIO)
    {
        return 0;
    }

    inventario->objetos[inventario->cantidad] = objeto;
    inventario->cantidad++;

    return 1;
}
int seleccionarObjetoInventario(Inventario* inventario)
{
    char tecla;
    int indice;

    system("cls");

    printf("Inventario\n\n");

    if(inventario->cantidad == 0)
    {
        printf("El inventario esta vacio.\n");
        printf("\n--presiona cualquier tecla para continuar--");
        getch();
        return -1;
    }
    else
    {
        for(int i = 0; i < inventario->cantidad; i++)
        {
            printf("%c) ", 'a' + i);

            switch(inventario->objetos[i].tipo)
            {
                case OBJ_POCION:
                    printf("Una pocion");
                    break;
                case OBJ_COMIDA:
                    printf("Algo de comida");
                    break;
                case OBJ_ARMA:
                    printf("Un arma");
                    break;
                case OBJ_AMULETO:
                    printf("El Amuleto de Yendor");
                    break;
                default:
                    printf("Un item desconocido");
                    break;
            }

            printf("\n");
        }
    }

    printf("\nPresiona la letra del objeto para usarlo.");
    printf("\nPresiona ESC para cancelar.");

    tecla = getch();

    if(tecla == 27)
    {
        return -1;
    }

    indice = tecla - 'a';

    if(indice < 0 || indice >= inventario->cantidad)
    {
        return -1;
    }

    return indice;
}

void dibujarObjetosNivel(Nivel* nivel)
{
    for(int i = 0; i < nivel->cantObjetos; i++)
    {
        if(nivel->objetos[i].activo) //Recorre todos los objetos que estan en el nivel. Si estan activos, los pone en el mapa
        {
            nivel->mapa[nivel->objetos[i].y][nivel->objetos[i].x]=nivel->objetos[i].representacion;
        }
    }

    for(int i = 0; i < nivel->cantOro; i++) //Objetos por un lado, oro y amuleto por el otro
    {
        if(nivel->oro[i].activo)
        {
            nivel->mapa[nivel->oro[i].y][nivel->oro[i].x]=nivel->oro[i].representacion;
        }
    }

    if(nivel->amuletoGenerado && nivel->amuleto.activo)
    {
        nivel->mapa[nivel->amuleto.y][nivel->amuleto.x]=nivel->amuleto.representacion;
    }
}

void generarObjetosNivel(Nivel* nivel)
{
    nivel->cantObjetos = h_numAleatorio(4, MAX_OBJETOS_NIVEL);

    for(int i = 0; i < nivel->cantObjetos; i++)
    {
        int secy = h_numAleatorio(0, nivel->filas - 1); //habitacion aleatoria
        int secx = h_numAleatorio(0, nivel->columnas - 1);

        Habitacion hab = nivel->habitaciones[secy][secx];

        int x = h_numAleatorio(hab.x + 1, hab.x + hab.w - 2); //posicion interna de la habitacion

        int y = h_numAleatorio(hab.y + 1, hab.y + hab.h - 2);

        int tipo = h_numAleatorio(OBJ_POCION, OBJ_ARMA); //tipo aleatorio de objeto

        nivel->objetos[i] = crearObjeto(tipo, x, y);
    }
}

void generarOroNivel(Nivel* nivel)
{
    nivel->cantOro = h_numAleatorio(2, MAX_ORO_NIVEL);

    for(int i = 0; i < nivel->cantOro; i++)
    {
        int secy = h_numAleatorio(0, nivel->filas - 1);

        int secx = h_numAleatorio(0, nivel->columnas - 1);

        Habitacion hab = nivel->habitaciones[secy][secx];

        int x = h_numAleatorio(hab.x + 1, hab.x + hab.w - 2);

        int y = h_numAleatorio(hab.y + 1, hab.y + hab.h - 2);

        Objeto oro = crearObjeto(OBJ_ORO, x, y);

        oro.valor = h_numAleatorio(0,50 + 10 * nivel->nivelDungeon) + 2;
        //Habria que agregar un apartado al struct Nivel que fuera mostrando en q piso estas para ir variando las recompensas obtenidas
        //o sino podemos mantenerlo fijo

        nivel->oro[i] = oro;
    }
}

int buscarObjetoEnPosicion(Nivel* nivel, int x, int y)
{
    for(int i = 0; i < nivel->cantObjetos; i++)
    {
        if(nivel->objetos[i].activo && nivel->objetos[i].x == x && nivel->objetos[i].y == y)
        {
            return i;
        }
    }

    return -1;
}

int buscarOroEnPosicion(Nivel* nivel, int x, int y)
{
    for(int i = 0; i < nivel->cantOro; i++)
    {
        if(nivel->oro[i].activo && nivel->oro[i].x == x && nivel->oro[i].y == y)
        {
            return i;
        }
    }

    return -1;
}

void recogerObjeto(Nivel* nivel, Jugador* jugador, int x, int y)
{
    int posOro = buscarOroEnPosicion(nivel, x, y);

    if(posOro != -1)
    {
        jugador->oro += nivel->oro[posOro].valor;
        nivel->oro[posOro].activo = 0;
        nivel->mapa[y][x] = '.';
        return;
    }

    int posObjeto = buscarObjetoEnPosicion(nivel, x, y);

    if(posObjeto != -1)
    {
        if(agregarObjetoInventario(&jugador->inventario, nivel->objetos[posObjeto]))
        {
            nivel->objetos[posObjeto].activo = 0;
            nivel->mapa[y][x] = '.';
        }
    }
}

void eliminarObjetoInventario(Inventario* inventario, int indice)
{
    for(int i = indice; i < inventario->cantidad - 1; i++)
    {
        inventario->objetos[i] = inventario->objetos[i + 1];
    }

    inventario->cantidad--;
}

int usarObjetoInventario(Jugador* jugador, int indice)
{
    if(indice < 0 || indice >= jugador->inventario.cantidad)
    {
        return 0;
    }

    Objeto obj = jugador->inventario.objetos[indice];

    switch(obj.tipo)
    {
        case OBJ_POCION:
             if(jugador->hp == jugador->hpMax) //pocion aumenta la hpMax en caso de que tenga full vida
            {
                jugador->hpMax += obj.valor;
                jugador->hp = jugador->hpMax;
            }
            else
            {
                jugador->hp += obj.valor;

                if(jugador->hp > jugador->hpMax) //en caso de q no este a full vida, cura cierta cantidad (como maximo hpMax)
                {
                    jugador->hp = jugador->hpMax;
                }
            }

            eliminarObjetoInventario(&jugador->inventario, indice);
            return 1;

        case OBJ_COMIDA:
            jugador->hp += obj.valor;

            if(jugador->hp > jugador->hpMax)
                jugador->hp = jugador->hpMax;

            eliminarObjetoInventario(&jugador->inventario, indice);
            return 1;

        case OBJ_ARMA:
            // por ahora no hacemos nada hasta que exista daño/arma equipada
            return 0;
    }

    return 0;
}
