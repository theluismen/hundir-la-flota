#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "prototipos.h"

int main () {
    srand(time(NULL));
    struct Juego juego;

    juego_init( &juego );

    generar_barcos( &juego );

    tablero_mostrar( &juego );

    juego_fin( &juego );
    return 0;
}
