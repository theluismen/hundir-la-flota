/* Constantes del juego */
#define TAM_TABLERO 10      //Tamaño tablero de juego
#define NO_BARCOS   10      //Numero total de barcos

/* Distintas direcciónes para colocar los barcos */
#define DIR_HO  1           //Dirección HOrizontal
#define DIR_HF  1           //Dirección Horizontal Forward
#define DIR_HB -1           //Dirección Horizontal Backward
#define DIR_VF  2           //Dirección Vertical   Forward
#define DIR_VB -2           //Dirección Vertical   Backward

/* Distintos caracteres a mostrar en la funcion void tablero_mostrar() */
#define CHAR_VACIO   ' '
#define CHAR_OCUPADO '#'
#define CHAR_AGUA    '~'
#define CHAR_TOCADO  'X'
#define CHAR_HUNDIDO 'H'

/* Estados de as casillas de tipo Casilla_t de juego->tablero */
#define CASILLA_VACIA   0
#define CASILLA_OCUPADA 1
#define CASILLA_AGUA    2
#define CASILLA_TOCADA  3
#define CASILLA_HUNDIDA 4
