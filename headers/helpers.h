#ifndef HELPERS_H
#define HELPERS_H

#define ABS(x)    ((x) > 0 ? (x) : -(x))
#define MIN(x, y) ((x) > (y) ? (y) : (x))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

// Codigo de escape ANSI: \x1B
// Esto lo vamos a usar tambien para el tema de actualizar la pantalla sin renderizar TODO el texto de nuevo
// Porque se puede usar para mover el cursor de la consola, y se me ocurre que podemos hacer algo de "sobreescribir" en el spot
// Lo voy a hacer este finde (15/05)
// Dario: msg se espera que sea "texto"
#define ROJO_BOLD       "\x1B[1;31m"
#define ROJO            "\x1B[31m"
#define AZUL_BOLD       "\x1B[1;34m"
#define AZUL            "\x1B[34m"
#define VERDE_BOLD      "\x1B[1;32m"
#define VERDE           "\x1B[32m"

#define COLOR_DEFAULT   "\x1B[39m"

#define TEXTO_ROJO_BOLD(msg)    (ROJO_BOLD msg)
#define TEXTO_ROJO(msg)         (ROJO msg)
#define TEXTO_AZUL_BOLD(msg)    (AZUL_BOLD msg)
#define TEXTO_AZUL(msg)         (AZUL msg)
#define TEXTO_VERDE_BOLD(msg)   (VERDE_BOLD msg)
#define TEXTO_VERDE(msg)        (VERDE msg)

int h_numAleatorio(int, int);
void h_limpiarColor();

#endif // HELPERS_H
