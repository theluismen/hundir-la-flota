#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "prototipos.h"

int main () {
    /* INICIALIZACIÓN de variables y estructuras */
    struct Juego juego;

    /* INICIO DEL JUEGO*/
    juego_init( &juego );       // Inicializar parametros del juego
    randomize();                // Iniciar numeros aleatorios

    generar_barcos( &juego );

    tablero_mostrar( &juego );

    juego_fin( &juego );

    return 0;
}
