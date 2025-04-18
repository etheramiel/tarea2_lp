#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "acciones.h"
#include "main.h"

extern Jugador* jugador;
extern Juego* juego;


void cocinar(void* contexto, int x, int y) {
    Tablero* tablero = juego->tablero;

    printf("=====Ingredientes en inventario=====\n");
    int opciones[5];
    int nuevo_x, nuevo_y;
    int total_opciones = 0;

    for(int i = 0; i<5; i++){
        Ingrediente *ing = juego->inventario[i];
        if(ing !=NULL && ing->estado == 0){
            printf("%d. %s\n", total_opciones + 1, ing->nombre);
            opciones[total_opciones] = i;
            total_opciones++;
        }
    }

    if (total_opciones == 0) {
        printf("No hay ingredientes crudos para cocinar.\n");
        return;
    }

    printf("Seleccione el ingrediente que desea cocinar (ingrese numero): ");
    int seleccion;
    scanf("%d", &seleccion);

    if (seleccion < 1 || seleccion > total_opciones) {
        printf("Seleccion invalida.\n");
        return;
    }

    int index = opciones[seleccion - 1];
    Ingrediente* ing = juego->inventario[index];



    if(strcmp(ing->nombre, "pollo") == 0){
        ing->estado = 2; //frito
    }
    else if(strcmp(ing->nombre, "hamburguesa") == 0){
        ing->estado = 3; //cocinado
    }
    else if(strcmp(ing->nombre, "arroz") == 0){
        ing->estado = 3; //cocinado
    }
    else if(strcmp(ing->nombre, "pasta") == 0){
        ing->estado = 3; //cocinado
    }
    else if(strcmp(ing->nombre, "lechuga") == 0){
        printf("Lechuga no se puede cocinar");
    }
    else if(strcmp(ing->nombre, "tomate") == 0){
        printf("Tomate no se puede cocinar");
    }
    else if(strcmp(ing->nombre, "papa") == 0){

        if(ing->estado == 1){
            ing->estado = 4;
        }
        else{
            printf("La papa debe estar cortada antes de freír.\n");
            return;
        }
    }

    printf("Cocinando %s por %d turnos...\n", ing->nombre, ing->turnos_elaboracion);
    juego->turnos_restantes -= ing->turnos_elaboracion;

    int r = rand() % 100;
    if(r<ing->prob_incendio){
        printf("¡INCENDIO! El ingrediente se ha quemado y la estación está en llamas.\n");

        free(juego->inventario[index]);
        juego->inventario[index] = NULL;

        Estacion* est = (Estacion*)tablero->celdas[y][x];
        est->simbolo = 'F';

        do {
            nuevo_x = rand() % tablero->columnas;
            nuevo_y = rand() % tablero->filas;
        } while (tablero->celdas[nuevo_y][nuevo_x] != NULL);

        jugador->x = nuevo_x;
        jugador->y = nuevo_y;

        printf("Fuiste reposicionado a (%d, %d).\n", nuevo_x, nuevo_y);
    } else {
        printf("Cocción completada exitosamente.\n");

    }
}

void buscar_ingrediente(void* contexto, int x, int y) {
    const char* ingredientes_disponibles[] = {
        "pan", "lechuga", "tomate", "arroz", "pasta",
        "hamburguesa", "pollo", "papa"
    };

    int cant_ingredientes = 8;
    int ing_elegido = rand() % cant_ingredientes;

    char* nombre_ing = ingredientes_disponibles[ing_elegido];
    printf("Encontraste %s!\n", nombre_ing);
    printf("¿Deseas guardarlo en el inventario? (1.Sí / 2.No): ");
    int respuesta;
    scanf("%d", &respuesta);

    if(respuesta != 1){
        printf("%s descartado", nombre_ing);
        return;
    }

    int espacio_vacio = -1;
    for(int i = 0; i<5; i++){
        if(juego->inventario[i] == NULL){
            espacio_vacio = i;
            break;
        }
    }

    if(espacio_vacio == -1){
        printf("Inventario lleno. No se pudo agregar%s\n", nombre_ing);
        return;
    }

    Ingrediente* nuevo = malloc(sizeof(Ingrediente));
    strcpy(nuevo->nombre, nombre_ing);
    nuevo->estado = 0;
    nuevo->es_extintor = 0;

    if(strcmp(nuevo->nombre, "pollo") == 0){
        nuevo->turnos_elaboracion = 5;
        nuevo->prob_incendio = 5;
    }
    else if(strcmp(nuevo->nombre, "hamburguesa") == 0){
        nuevo->turnos_elaboracion = 3;
        nuevo->prob_incendio = 3;
    }
    else if(strcmp(nuevo->nombre, "arroz") == 0){
        nuevo->turnos_elaboracion = 2;
        nuevo->prob_incendio = 1;
    }
    else if(strcmp(nuevo->nombre, "pasta") == 0){
        nuevo->turnos_elaboracion = 2;
        nuevo->prob_incendio = 1;
    }
    else if(strcmp(nuevo->nombre, "lechuga") == 0){
        nuevo->turnos_elaboracion = 1;
        nuevo->prob_incendio = 0;
    }
    else if(strcmp(nuevo->nombre, "tomate") == 0){
        nuevo->turnos_elaboracion = 1;
        nuevo->prob_incendio = 0;
    }
    else if(strcmp(nuevo->nombre, "papa") == 0){
        nuevo->turnos_elaboracion = 4;
        nuevo->prob_incendio = 2;
    }

    juego->inventario[espacio_vacio] = nuevo;
    printf("%s agregado al inventario (espacio %d).\n", nombre_ing, espacio_vacio);
}

void cortar(void* contexto, int x, int y) {
    Tablero* tablero = juego->tablero;

    printf("=====Ingredientes en inventario=====\n");
    int opciones[5];
    int total_opciones = 0;

    for(int i = 0; i<5; i++){
        Ingrediente *ing = juego->inventario[i];
        if(ing !=NULL && ing->estado == 0){
            printf("%d. %s\n", total_opciones + 1, ing->nombre);
            opciones[total_opciones] = i;
            total_opciones++;
        }
    }

    if (total_opciones == 0) {
        printf("No hay ingredientes para cortar.\n");
        return;
    }

    printf("Seleccione el ingrediente que desea cortar (ingrese numero): ");
    int seleccion;
    scanf("%d", &seleccion);

    if (seleccion < 1 || seleccion > total_opciones) {
        printf("Seleccion invalida.\n");
        return;
    }

    int index = opciones[seleccion - 1];
    Ingrediente* ing = juego->inventario[index];



    if(strcmp(ing->nombre, "pollo") == 0){
        printf("Pollo no se puede cortar");
    }
    else if(strcmp(ing->nombre, "hamburguesa") == 0){
        printf("Hamburguesa no se puede cortar");
    }
    else if(strcmp(ing->nombre, "arroz") == 0){
        printf("Arroz no se puede cortar");
    }
    else if(strcmp(ing->nombre, "pasta") == 0){
        printf("Pasta no se puede cortar");
    }
    else if(strcmp(ing->nombre, "lechuga") == 0){
       ing->estado = 1;
    }
    else if(strcmp(ing->nombre, "tomate") == 0){
        ing->estado = 1;
    }
    else if(strcmp(ing->nombre, "papa") == 0){
        ing->estado = 1;
    }

    printf("Cortando %s por %d turnos...\n", ing->nombre, ing->turnos_elaboracion);
    juego->turnos_restantes -= ing->turnos_elaboracion;
    printf("Ingrediente cortado con exito");
}

void apagar_incendio(void* contexto, int x, int y) {
    printf("Acción: apagar incendio en (%d, %d)\n", x, y);
}

void entregar_pedido(void* contexto) {
    printf("Acción: entregar pedido\n");
}
