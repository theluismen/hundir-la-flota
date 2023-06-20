#include <stdlib.h>
#include <stdbool.h>
#include "tipos.h"
#include "defines.h"

/* Función que devuelve la longitud del barco segun el indice barco_i
barco_i     longt
0           4
1-2         3
3-5         2
6-9         1
*/
short int barco_longt ( short int barco_i ) {
    short int longt = 1;

    if ( barco_i == 0 )
        longt = 4;
    else if ( barco_i < 3 )
        longt = 3;
    else if ( barco_i < 6 )
        longt = 2;

    return longt;
}

/* Generar coordenadas x, y, y dirección aleatorias. Asume que el barco no se puede colocar */
void barco_init_coord ( struct Barco * barco ) {
    barco->x         = rand() % TAM_TABLERO;
    barco->y         = rand() % TAM_TABLERO;
    barco->dir       = rand() % 2 + 1;
    barco->dir       = (rand() % 2 == 0) ? -barco->dir : barco->dir;
    barco->colocable = false;
}

/* Funcion que devuelve true/false si el barco cabe o no en el tablero.
Los criterios se basan en sus coordenadas. */
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

/* Funcion que comprueba si el area requerida por un barco para ser colocado (perimetro libre), realmente esta vacia.
   Se trata de delimitar el area y comprobar que no hay barcos */
bool barco_colocable ( struct Juego * juego, struct Barco * barco ) {
    short int i, j;                 // Var iterativas i -> columna, j -> fila
    short int fila_ini, col_ini;    // Var que delimitan el inicio de la zona a mirar
    short int fila_end, col_end;    // Var que delimitan el final  de la zona a mirar
    bool colocable = true;          // Barco colocable. Se asume que si

    /* Delimitar AREA de region que ocupa barco */
    /*  NOTA - Es posible que cierta parte de la region se salga del tablero */
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

    /* Eliminar posibles fuera de rangos VERTICALES */
    if ( fila_ini < 0 ) {                   // Se sale por ARRIBA
        fila_ini++;
    } else if ( fila_end > TAM_TABLERO ) {  // Se sale por ABAJO
        fila_end--;
    }

    /* Eliminar posibles fuera de rangos HORIZONTALES */
    if ( col_ini < 0 ) {                    // Se sale por la IZQUIERDA
        col_ini++;
    } else if ( col_end > TAM_TABLERO ) {   // Se sale por la DERECHA
        col_end--;
    }

    /* Comprovar el AREA. Se trata de BUSCAR un caracter diferente a el que indica un barco o trozo de este */
    for ( i = fila_ini ; i <= fila_end && colocable ; i++ ) {
        for ( j = col_ini ; j <= col_end && colocable ; j++ ) {
            colocable = juego->tablero[i * TAM_TABLERO + j] != '#';
        }
    }

    return colocable;
}

/* Dibuja o coloca el barco en el juego->tablero. SE ASUME QUE SE PUEDE COLOCAR.*/
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

/* Funcion que genera los barcos en el tablero.
 Esta función depende de TODAS las funciones anteriores en este archivo
*/
void generar_barcos ( struct Juego * juego ) {
    int barco_index;

    /* Cada iteracion del for finalmente coloca un barco*/
    for ( barco_index = 0; barco_index < NO_BARCOS; barco_index++ ) {
        struct Barco barco;                         // Declarar un struct tipo Barco
        barco.longt = barco_longt( barco_index );   // Darle al barco la logitud que corresponda

        /* Bucle que se repite HASTA que se genera un barco que CABE y se PUEDE COLOCAR */
        do {
            barco_init_coord( &barco );             // Escoger coordenadas y dirección aleatorias
            if ( barco_cabe( &barco ) )
                barco.colocable = barco_colocable( juego, &barco );

        } while ( ! barco.colocable );

        /* Finalmente colocar el barco */
        barco_colocar( juego, &barco );
    }
}
