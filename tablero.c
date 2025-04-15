#include <stdlib.h> 
#include <stdio.h>

#include "tablero.h"
#include "acciones.h"
#include "main.h"

Jugador* jugador;

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
    generarEstacionAleatoria(tablero, 'T', cortar);
    generarEstacionAleatoria(tablero, 'E', apagar_incendio);
    generarEstacionAleatoria(tablero, 'A', buscar_ingrediente);
    generarEstacionAleatoria(tablero, 'C', cocinar);
    
}

void actualizarCelda (Tablero * tablero , int x , int y , void *elemento ){
    tablero->celdas[x][y] = elemento;
}


void generarEstacionAleatoria(Tablero* tablero, char simbolo, void (*accion)(void*, int, int)){
    int x, y;

    do{
        x = rand() % tablero->filas;
        y = rand() % tablero->columnas;
    }while(tablero->celdas[x][y] != NULL);

    Estacion* estacion = malloc(sizeof(Estacion));
    estacion->simbolo = simbolo;
    estacion->accion = accion;
    estacion->en_llamas = 0;
    estacion->turnos_inhabilitada = 0;
    
    actualizarCelda(tablero, x, y, estacion);
    
}



void mostrarTablero (Tablero* tablero){
    for(int i = 0; i<tablero->filas; i++){
        for(int j = 0; j<tablero->columnas; j++){
            if(i == jugador->x && j == jugador->y){
                printf("O ");
            }
            else if(tablero->celdas[i][j] == NULL){
                printf(". ");
            }
            else{
                Estacion* e = (Estacion*)tablero->celdas[i][j];
                printf("%c ", e->simbolo);
            }
        }
        printf("\n");
    }
}
