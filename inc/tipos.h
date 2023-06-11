#include <stdbool.h>

struct Juego {
    short int no_barcos_hundidos;
    char * tablero;
};

struct Barco {
    //short int index;
    short int x;
    short int y;
    short int dir;
    short int longt;
    bool colocable;
};
