#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "tipos.h"
#include "defines.h"
#include "prototipos.h"

/* Iniciar numeros aleatorios*/
void randomize ( void ) {
    srand(time(NULL));
}

/* Inicializar parametros del juego; valores por defecto, caracteres en el tablero y todo eso */
void juego_init ( struct Juego * juego ) {
    short int i, j;

    juego->no_barcos_hundidos = 0;
    /* Asignar memoria para el tablero */
    juego->tablero = malloc( TAM_TABLERO * TAM_TABLERO * sizeof( Casilla_t ) );
    /* Inicializar Tablero con caracteres vacios */
    for ( i = 0; i < TAM_TABLERO; i++) {
        for ( j = 0; j < TAM_TABLERO; j++) {
            juego->tablero[ i * TAM_TABLERO + j ] = CASILLA_VACIA;
        }
    }
    /* Asignar memoria para guardar los barcos colocados */
    juego->barcos = malloc( NO_BARCOS * sizeof( struct Barco ) );
}

/* Acabar juego. Basicamente para hacer el free() */
void juego_fin ( struct Juego * juego ) {
    /* Liberar memoria reservada para el tablero del juego Y guardar barcos */
    free(juego->tablero);
    free(juego->barcos);
}

/* Mostrar tablero */
void tablero_mostrar ( struct Juego * juego ) {
    short int i, j;
    unsigned char caracter;

    printf("  ");
    for ( i = 0; i < TAM_TABLERO; i++ ) {
        printf("%d ", i);
    }

    printf("\n");
    for ( i = 0; i < TAM_TABLERO; i++ ) {
        printf("%d|", i);
        for ( j = 0; j < TAM_TABLERO; j++) {
            switch ( juego->tablero[ i * TAM_TABLERO + j ] ) {
                case CASILLA_VACIA   : caracter = CHAR_VACIO;   break;
                case CASILLA_OCUPADA : caracter = CHAR_OCUPADO; break;
                case CASILLA_TOCADA  : caracter = CHAR_TOCADO;  break;
                case CASILLA_HUNDIDA : caracter = CHAR_HUNDIDO; break;
            }
            printf("%c ", caracter);
        }
        printf("|\n");
    }
}

/* Funcion que determina cuando se acaba el juego -*/
bool juego_acabado ( struct Juego * juego ) {
    return ( juego->no_barcos_hundidos == NO_BARCOS );
}

/* Pide las coordenadas de la jugada y actualiza el tablero si adivina la casilla */
void hacer_jugada ( struct Juego * juego ) {
    short int x, y;
    bool formato_ok = true;

    /* Pedir las coordenadas del usuario HASTA que sean correctas */
    do {
        if ( ! formato_ok ) {
            printf("ERROR: Formato Invalido\n");
        }
        printf("Coord (N,N): ");
        scanf("%hd,%hd", &y, &x);
        formato_ok = ( x >= 0 && x < TAM_TABLERO && y >= 0 && y < TAM_TABLERO );
    } while ( ! formato_ok );

    /* Pasar de CASILLA_OCUPADA a CASILLA_TOCADA si el usuario acierta*/
    if ( juego->tablero[ y * TAM_TABLERO + x ] == CASILLA_OCUPADA ) {
        juego->tablero[ y * TAM_TABLERO + x ] = CASILLA_TOCADA;
    }

}

bool barco_hundido ( struct Juego * juego, struct Barco * barco ) {
    bool hundido = true;
    int i, aux = 0;
    for ( i = 0; i < barco->longt && hundido; i++) {
        if ( abs(barco->dir) == DIR_HO ) {
            hundido = juego->tablero[barco->y * TAM_TABLERO + barco->x + aux] == CASILLA_TOCADA;
        } else {
            hundido = juego->tablero[(barco->y + aux)*TAM_TABLERO + barco->x] == CASILLA_TOCADA;
        }
        aux = ( barco->dir > 0 ) ? aux+1 : aux-1;
    }
    return hundido;
}

void juego_actualizar ( struct Juego * juego ) {
    int barco_index;

    /* Para cada uno de los barcos no hundidos */
    for ( barco_index = 0; barco_index < (NO_BARCOS - juego->no_barcos_hundidos); barco_index++) {
        struct Barco barco;
        /* Guardar los datos del barco sin hundir actual en un struct Barco para trabajar mejor */
        barco.x     = juego->barcos[barco_index].x;
        barco.y     = juego->barcos[barco_index].y;
        barco.dir   = juego->barcos[barco_index].dir;
        barco.longt = juego->barcos[barco_index].longt;

        /* Comprovar si todo el barco esta TOCADO */
        if ( barco_hundido( juego, &barco ) ) {
            barco_colocar_con( juego, &barco, CASILLA_HUNDIDA );
        }
    }
}
