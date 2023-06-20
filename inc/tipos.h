#include <stdbool.h>

struct Juego {
    short int no_barcos_hundidos;  // Nº de barcos Hundidos
    char * tablero;                // Puntero del tablero donde habra los barcos
};

struct Barco {
    short int x;                   // Coord X
    short int y;                   // Coord Y
    short int dir;                 // Dirección de Barco
    short int longt;               // Longitud de Barco
    bool colocable;                // Si el barco es COLOCABLE
};                                 //  que sea colocable implica que previamente CABE
