#include "tipos.h"

/* Archivo common.c */
void randomize ( void );
void juego_init( struct Juego * juego );
void juego_fin ( struct Juego * juego );
void tablero_mostrar ( struct Juego * juego );

/* Archivo generar.c */
short int barco_longt ( short int barco_i );
void barco_init_coord ( struct Barco * barco );
bool barco_cabe ( struct Barco * barco );
bool barco_colocable ( struct Juego * juego, struct Barco * barco );
void barco_colocar ( struct Juego * juego, struct Barco * barco );
void generar_barcos ( struct Juego * juego );
