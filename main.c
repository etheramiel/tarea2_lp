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
    juego->tablero = tablero;
    // juego->inventario = crearInventario();


    if(dificultad == 1){
        filas = columnas = 5;
        pedidos = 3;
        juego->turnos_restantes = 60;
        juego->dificultad = 1;
    }else if (dificultad == 2){
        filas = columnas = 10;
        pedidos = 4;
        juego->turnos_restantes = 60;
        juego->dificultad = 2;
    }else{
        filas = columnas = 10;
        pedidos = 5;
        juego->turnos_restantes = 45;
        juego->dificultad = 3;
    }

    inicializarTablero(tablero, filas, columnas);

    jugador = malloc(sizeof(Jugador));

    do {
        jugador->x = rand() % filas;
        jugador->y = rand() % columnas;
    } while (tablero->celdas[jugador->x][jugador->y] != NULL);

    mostrarTablero(tablero);

    while(juego->turnos_restantes > 0 && pedidos > 0){
        char accion;
        int casillas;
        printf("Que desea hacer:\n1.Moverse\n2.Accion\n3.Ver Inventario\n4.Entregar Plato\n5.Salir del juego\n");
        scanf(" %c", &accion);
        if(accion == '1'){
            char direccion;
            printf("Ingrese direccion (W, A, S, D): ");
            scanf(" %c", &direccion);
            printf("Ingrese cantidad de casillas: ");
            scanf(" %d", &casillas);
            moverJugador(tablero, casillas, direccion);
            mostrarTablero(tablero);
        }else if(accion == '2'){

        }else if(accion == '3'){

        }else if(accion == '4'){

        }else if(accion == '5'){
            break;
        }
        pedidos--;
    }
    return 0;
}

