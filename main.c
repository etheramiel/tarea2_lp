#include <stdio.h>
#include <stdlib.h>

#include "acciones.h"
#include "tablero.h"
#include "inventario.h"
#include "main.h"

extern Jugador* jugador;

int main(){
    printf("Seleccione dificultad:\n1.Facil\n2.Medio\n3.Dificil\n");
    int dificultad, filas, columnas, turnos, pedidos;
    scanf("%d", &dificultad);
    Tablero* tablero = malloc(sizeof(Tablero));

    if(dificultad == 1){
        filas = columnas = 5;
        turnos = 60;
        pedidos = 3;
    }else if (dificultad == 2){
        filas = columnas = 8;
        turnos = 50;
        pedidos = 4;
    }else{
        filas = columnas = 10;
        turnos = 45;
        pedidos = 5;
    }

    inicializarTablero(tablero, filas, columnas);

    jugador = malloc(sizeof(Jugador));

    do {
        jugador->x = rand() % filas;
        jugador->y = rand() % columnas;
    } while (tablero->celdas[jugador->y][jugador->x] != NULL);

    mostrarTablero(tablero);

    return 0;
}

