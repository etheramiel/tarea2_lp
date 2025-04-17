#include <stdlib.h>
#include "main.h"
#include "inventario.h"
extern Juego* juego;

void crearInventario (){
    juego->inventario = (Ingrediente**)malloc(5 * sizeof(Ingrediente*));
    for(int i = 0; i <5; i++){
        juego->inventario[i] = NULL;
    }
}

void liberarInventario(){
    for(int i = 0; i<5; i++){
        if(juego->inventario[i] != NULL){
            free(juego->inventario[i]);
        }
    }
    free(juego->inventario);
}