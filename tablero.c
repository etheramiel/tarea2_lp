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
    if(tablero->celdas[x][y] == NULL){
        tablero->celdas[x][y] = elemento;
    }
    else if(elemento == NULL){
        jugador->x = x;
        jugador->y = y;
    }

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
            if(tablero->celdas[i][j] == NULL && (i == jugador->y && j == jugador->x)){
                printf("O ");
            }
            else if(tablero->celdas[i][j] != NULL && (i == jugador->y && j == jugador->x)){
                printf("V ");
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


void moverJugador(Tablero* tablero, int casillas, char direccion){
    if(direccion == 'W'){
        jugador->y = jugador->y-casillas;
        if(jugador->y < 0){
            jugador->y = 0;
        } 
    }
    else if(direccion == 'S'){
        jugador->y = jugador->y+casillas;
        if(jugador->y > tablero->filas){
            jugador->y = tablero->filas - 1;
        } 
    }
    else if(direccion == 'D'){
        jugador->x = jugador->x+casillas;
        if(jugador->x > tablero->columnas){
            jugador->x = tablero->columnas - 1;
        }
    }
    else if(direccion == 'A'){
        jugador->x = jugador->x-casillas;
        if(jugador->x < 0){
            jugador->x = 0;
        } 
    }
}