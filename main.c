#include <stdio.h>
#include <stdlib.h>

#include "tablero.h"
#include "inventario.h"
#include "acciones.h"
#include "main.h"


//tablero.c
void inicializarTablero ( Tablero * tablero , int filas , int columnas){
    tablero->filas = filas;
    tablero->columnas = columnas;

    tablero->celdas = (void***)malloc(filas * sizeof(void***));

    for(int i = 0; i < filas; i++){
        tablero->celdas[i] = (void**)malloc(columnas * sizeof(void**));
        
        for(int j = 0; i<columnas; j++){
            tablero->celdas[i][j] = '.';
        }
    }
}

void mostrarTablero (Tablero* tablero){
    for(int i = 0; i<tablero->filas; i++){
        for(int j = 0; i<tablero->columnas; j++){
            printf("%c", tablero->celdas[i][j]);
        }
    }
}

//----------------------------------------------------------------
int main(){
    printf("Seleccione dificultad:\n1.Facil\n2.Medio\n3.Dificil\n");
    int dificultad, filas, turnos, pedidos;
    scanf("%d", &dificultad);
    printf("%d\n", dificultad);
    Tablero* tablero = malloc(sizeof(Tablero));

    if(dificultad == 1){
        filas = 5;
        turnos = 60;
        pedidos = 3;
    }else if (dificultad == 1){
        filas = 8;
        turnos = 50;
        pedidos = 4;
    }else{
        filas = 10;
        turnos = 45;
        pedidos = 5;
    }

    inicializarTablero(tablero, filas, filas);
    mostrarTablero(tablero);

    return 0;
}