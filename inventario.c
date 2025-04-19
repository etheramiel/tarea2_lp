#include <stdlib.h>
#include <stdio.h>
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

void verInventario (){
    const char* estados[] = {"crudo", "cortado", "frito", "cocinado", "cortado y frito"};

    int vacio = 1;
    printf("======= Inventario =======\n");
    for (int i = 0; i < 5; i++) {
        Ingrediente* ing = juego->inventario[i];
        if (ing != NULL) {
            vacio = 0;
            if (ing->es_extintor) {
                printf("%d. EXTINTOR (espacio %d)\n", i + 1, i);
            } else {
                printf("%d. %s | Estado: %s\n", i + 1, ing->nombre, estados[ing->estado]);
            }
        }
    }
    if (vacio) {
        printf("Inventario vacío.\n");
    }
    printf("==========================\n");
}
