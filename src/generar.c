#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tipos.h"
#include "defines.h"

short int barco_longt ( short int barco_i ) {
    short int longt = 1;

    if ( barco_i == 0)
        longt = 4;
    else if ( barco_i < 3 )
        longt = 3;
    else if ( barco_i < 6 )
        longt = 2;

    return longt;
}

void barco_init_coord ( struct Barco * barco ) {
    // barco->x    = 0;
    // barco->y    = 0;
    // barco->dir = 2;
    barco->x    = rand() % TAM_TABLERO;
    barco->y    = rand() % TAM_TABLERO;
    barco->dir  = rand() % 2 + 1;
    barco->dir  = (rand() % 2 == 0) ? -barco->dir : barco->dir;
    barco->colocable = false;
}

bool barco_cabe ( struct Barco * barco ) {
    bool cabe;
    switch ( barco->dir ) {
        case DIR_HF:
            cabe = barco->x + barco->longt - 1 <= TAM_TABLERO; break;
        case DIR_HB:
            cabe = barco->x - barco->longt + 1 >= 0; break;
        case DIR_VF:
            cabe = barco->y + barco->longt - 1 <= TAM_TABLERO; break;
        case DIR_VB:
            cabe = barco->y - barco->longt + 1 >= 0; break;
    }
    return cabe;
}

bool barco_colocable ( struct Juego * juego, struct Barco * barco ) {
    short int i, j;
    short int fila_ini, col_ini;
    short int fila_end, col_end;
    bool colocable = true;

    /* Decidir límites de region que ocupa barco */
    /*  aqui es posible que cierta parte de la region se salga del tablero */

    if ( abs(barco->dir) == 1 ) {
        fila_ini = barco->y - 1;
        fila_end = barco->y + 1;

        col_ini = barco->x - 1;
        col_end = barco->x + barco->longt;

        if ( barco->dir == DIR_HB ) {
            col_ini = barco->x - barco->longt;
            col_end = barco->x + 1;
        }
    } else {
        fila_ini = barco->y - 1;
        fila_end = barco->y + barco->longt;

        col_ini = barco->x - 1;
        col_end = barco->x + 1;

        if ( barco->dir == DIR_VB ) {
            fila_ini = barco->y - barco->longt;
            fila_end = barco->y + 1;
        }
    }

    // printf("FILA_INI:%d\nFILA_END:%d\nCOL_INI:%d\nCOL_END:%d\n", fila_ini, fila_end, col_ini, col_end);
    if ( fila_ini < 0 ) { // salirse por arriba
        fila_ini++;
    } else if ( fila_end > TAM_TABLERO ) { // salirse por abajo
        fila_end--;
    }

    if ( col_ini < 0 ) { // salirse por la izquierda
        col_ini++;
    } else if ( col_end > TAM_TABLERO ) { // salirse por abajo
        col_end--;
    }

    // printf("FILA_INI:%d\nFILA_END:%d\nCOL_INI:%d\nCOL_END:%d\n", fila_ini, fila_end, col_ini, col_end);

    for ( i = fila_ini ; i <= fila_end && colocable ; i++ ) {
        for ( j = col_ini ; j <= col_end && colocable ; j++ ) {
            // printf("(%d,%d) => '%c'\n", i, j, juego->tablero[i * TAM_TABLERO + j] );
            colocable = juego->tablero[i * TAM_TABLERO + j] != '#';
            // juego->tablero[i * TAM_TABLERO + j] = '#';
        }
    }

    return colocable;
}

void barco_colocar ( struct Juego * juego, struct Barco * barco ) {
    int i, aux;

    aux = 0;
    for ( i = 0; i < barco->longt; i++) {
        if ( abs(barco->dir) == 1 ) {
            juego->tablero[barco->y * TAM_TABLERO + barco->x + aux] = '#';
        } else {
            juego->tablero[(barco->y + aux)*TAM_TABLERO + barco->x] = '#';
        }
        aux = (barco->dir > 0 ) ? aux+1 : aux-1;
    }
}

void generar_barcos ( struct Juego * juego ) {
    int barco_index;

    for ( barco_index = 0; barco_index < NO_BARCOS; barco_index++ ) {
        struct Barco barco;
        /* Setear longitud de barco en funcion de su indice */
        barco.longt = barco_longt( barco_index );

        do {
            /* Escoger coordenadas y dirección aleatorias */
            barco_init_coord( &barco );
            // printf("[%d]:%d:%d:%d:%d\n", barco_index, barco.x, barco.y, barco.dir, barco.longt );
            if ( barco_cabe( &barco ) ) {
                barco.colocable = barco_colocable( juego, &barco );
            }
        } while ( ! barco.colocable );

        barco_colocar( juego, &barco );
    }
}
