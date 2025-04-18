#ifndef MAIN_H
#define MAIN_H

#include "tablero.h"
#include "acciones.h"



typedef struct {
    Tablero * tablero ; // Puntero al struct Tablero
    Ingrediente ** inventario ;
    Pedido * pedidos ;
    int turnos_restantes ;
    int dificultad ;
} Juego ;


typedef struct {
    int x ; // Posicion X en el tablero
    int y ; // Posicion Y en el tablero
    int en_llamas ; // 1 si el jugador esta en llamas ( por atravesar estacion incendiada )
} Jugador ;

void crearMenu();
void mostrarMenu();

#endif



