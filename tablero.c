#include <stdlib.h> 
#include <stdio.h>

#include "tablero.h"


void inicializarTablero ( Tablero* tablero , int filas , int columnas){
    tablero->filas = filas;
    tablero->columnas = columnas;

    tablero->celdas = (void***)malloc(filas * sizeof(void**));

    for(int i = 0; i < filas; i++){
        tablero->celdas[i] = (void**)malloc(columnas * sizeof(void*));
        
        for(int j = 0; j<columnas; j++){
            tablero->celdas[i][j] = NULL;
        }
    }
}


void mostrarTablero (Tablero* tablero){
    for(int i = 0; i<tablero->filas; i++){
        for(int j = 0; j<tablero->columnas; j++){
            if(tablero->celdas[i][j] == NULL){
                printf(". ");
            }
        }
        printf("\n");
    }
}
