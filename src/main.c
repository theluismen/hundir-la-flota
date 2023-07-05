#include "tipos.h"
#include "prototipos.h"
//cd "/c/Users/luismen/Documents/URV Primer Curso/FP2/hundir-la-flota"

int main () {
    /* INICIALIZACIÓN de variables y estructuras */
    struct Juego juego;

    /* INICIO DEL JUEGO*/
    randomize();                // Iniciar numeros aleatorios
    juego_init( &juego );       // Inicializar parametros del juego

    generar_barcos( &juego );

    /* BUCLE PRINCIPAL DEL JUEGO */
    while ( ! juego_acabado( &juego ) ) {
        tablero_mostrar( &juego );
        hacer_jugada( &juego );
        juego_actualizar( &juego );
    }
    juego_fin( &juego );

    return 0;
}
