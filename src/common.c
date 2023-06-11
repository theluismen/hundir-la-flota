#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tipos.h"
#include "defines.h"

void randomize ( void ) {
    srand(time(NULL));
}

void juego_init ( struct Juego * juego ) {
    short int i, j;

    juego->no_barcos_hundidos = 0;
    /* Asignar memoria para el tablero */
    juego->tablero = malloc( TAM_TABLERO * TAM_TABLERO * sizeof(char) );
    /* Inicializar Tablero con caracteres vacios */
    for ( i = 0; i < TAM_TABLERO; i++) {
        for ( j = 0; j < TAM_TABLERO; j++) {
            juego->tablero[ i * TAM_TABLERO + j ] = DEF_CHAR;
        }
    }
}

void juego_fin ( struct Juego * juego ) {
    /* Liberar memoria reservada para el tablero del juego */
    free(juego->tablero);
}

void tablero_mostrar ( struct Juego * juego ) {
    short int i, j;
    printf("  ");
    for ( i = 0; i < TAM_TABLERO; i++ ) {
        printf("%d ", i);
    }
    printf("\n");
    for ( i = 0; i < TAM_TABLERO; i++ ) {
        printf("%d|", i);
        for ( j = 0; j < TAM_TABLERO; j++) {
            printf("%c ", juego->tablero[ i * TAM_TABLERO + j ]);
        }
        printf("|\n");
    }
}
