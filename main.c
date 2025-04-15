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
    Juego* juego = malloc(sizeof(Juego));


    if(dificultad == 1){
        filas = columnas = 5;
        juego->tablero;
        juego->turnos_restantes = 60;
        juego->dificultad = 1
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

    while(turnos > 0 && pedidos > 0){
        char accion;
        int casillas;
        printf("Que desea hacer:\n1.Moverse(W, A, S, D)\n2.Accion\n3.Ver Inventario\n4. Entregar Plato\n5.Salir del juego\n");
        scanf(" %c", &accion);
        if(accion == 'W'){
            printf("Ingrese cantidad de casillas: ");
            scanf("%d", &casillas);
        }else if(accion == 'A'){
            printf("Ingrese cantidad de casillas: ");
            scanf("%d", &casillas);
        }else if(accion == 'S'){
            printf("Ingrese cantidad de casillas: ");
            scanf("%d", &casillas);
        }else if(accion == 'D'){
            printf("Ingrese cantidad de casillas: ");
            scanf("%d", &casillas);
        }else if(accion == '2'){

        }else if(accion == '3'){

        }else if(accion == '4'){

        }else if(accion == '5'){

        }
        pedidos--;
    }

    return 0;
}

