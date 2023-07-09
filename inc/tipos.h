/* TIPO Casilla_t: sirve para definir el tablero como tabla (puntero) de este struct */
typedef unsigned char Casilla_t;

struct Juego {
    short int no_barcos_hundidos;  // Nº de barcos Hundidos
    Casilla_t * tablero;           // Puntero del tablero donde habra los barcos
    struct Barco * barcos;         // Guardar barcos colocados despues de la f generar_barcos()
};

struct Barco {
    short int x;                   // Coord X
    short int y;                   // Coord Y
    short int dir;                 // Dirección de Barco
    short int longt;               // Longitud de Barco
};
