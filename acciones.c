#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "acciones.h"
#include "main.h"

extern Jugador* jugador;
extern Juego* juego;


void cocinar(void* contexto, int x, int y) {
    Tablero* tablero = juego->tablero;

    Estacion* est = (Estacion*)tablero->celdas[y][x];
    if (est->turnos_inhabilitada > 0) {
        printf("La estación está inhabilitada por %d turnos más.\n", est->turnos_inhabilitada);
        return;
    }


    printf("=====Ingredientes en inventario=====\n");
    int opciones[5];
    int nuevo_x, nuevo_y;
    int total_opciones = 0;

    for(int i = 0; i<5; i++){
        Ingrediente *ing = juego->inventario[i];
        if(ing !=NULL && (ing->estado == 0 || ing->estado == 1) ){
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
        printf("Lechuga no se puede cocinar\n");
        return;
    }
    else if(strcmp(ing->nombre, "tomate") == 0){
        printf("Tomate no se puede cocinar\n");
        return;
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

    // int r = rand() % 100;
    int r = 1;
    if(r<ing->prob_incendio){
        printf("¡INCENDIO! El ingrediente se ha quemado y la estación está en llamas.\n");

        free(juego->inventario[index]);
        juego->inventario[index] = NULL;

        Estacion* est = (Estacion*)tablero->celdas[y][x];
        est->simbolo = 'F';
        est->accion = apagar_incendio; 

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
        printf("%s descartado\n", nombre_ing);
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
        printf("Inventario lleno. No se pudo agregar %s\n", nombre_ing);
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
        printf("Pollo no se puede cortar\n");
        return;
    }
    else if(strcmp(ing->nombre, "hamburguesa") == 0){
        printf("Hamburguesa no se puede cortar\n");
        return;
    }
    else if(strcmp(ing->nombre, "arroz") == 0){
        printf("Arroz no se puede cortar\n");
        return;
    }
    else if(strcmp(ing->nombre, "pasta") == 0){
        printf("Pasta no se puede cortar\n");
        return;
    }
    else if(strcmp(ing->nombre, "pan") == 0){
        printf("Pan no se puede cortar\n");
        return;
    }
    else if(strcmp(ing->nombre, "lechuga\n") == 0){
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
    printf("Ingrediente cortado con exito\n");
}


void entregar_pedido(void* contexto) {
    Juego* juego = (Juego*)contexto;

    int pedido_index = -1;
    int cant_pedidos;
    if (juego->dificultad == 1) {
        cant_pedidos = 3;
    } else if (juego->dificultad == 2) {
        cant_pedidos = 4;
    } else {
        cant_pedidos = 5;
    }

    for (int i = 0; i < cant_pedidos; i++) {
        if (juego->pedidos[i].completado == 0) {
            pedido_index = i;
            break;
        }
    }

    if (pedido_index == -1) {
        printf("No hay pedidos pendientes.\n");
        return;
    }

    Pedido* pedido = &juego->pedidos[pedido_index];
    int usados[5] = {0, 0, 0, 0, 0};

    for (int i = 0; pedido->ingredientes_requeridos[i] != NULL; i++) {
        Ingrediente* req = pedido->ingredientes_requeridos[i];
        int encontrado = 0;

        for (int j = 0; j < 5; j++) {
            Ingrediente* ing = juego->inventario[j];
            if (ing != NULL && !usados[j]
                && strcmp(ing->nombre, req->nombre) == 0
                && ing->estado == req->estado) {
                usados[j] = 1;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("No tienes todos los ingredientes requeridos para '%s'.\n", pedido->nombre_plato);
            return;
        }
    }

    printf("¡Pedido '%s' entregado exitosamente!\n", pedido->nombre_plato);
    pedido->completado = 1;

    for (int i = 0; i < 5; i++) {
        if (usados[i]) {
            free(juego->inventario[i]);
            juego->inventario[i] = NULL;
        }
    }
}

void apagar_incendio(void* contexto, int x, int y) {
    Juego* juego = (Juego*)contexto;
    Tablero* tablero = juego->tablero;
    Estacion* est = (Estacion*)tablero->celdas[y][x];

    // Revisar si el jugador ya tiene extintor
    int tiene_extintor = 0;
    for (int i = 0; i < 5; i++) {
        if (juego->inventario[i] && juego->inventario[i]->es_extintor == 1) {
            tiene_extintor = 1;
            break;
        }
    }

    // Caso 1: recolectar extintor desde estación 'E'
    if (est->simbolo == 'E' && !tiene_extintor) {
        // Vaciar inventario
        for (int i = 0; i < 5; i++) {
            if (juego->inventario[i] != NULL) {
                free(juego->inventario[i]);
                juego->inventario[i] = NULL;
            }
        }

        // Agregar extintor
        Ingrediente* extintor = malloc(sizeof(Ingrediente));
        strcpy(extintor->nombre, "EXTINTOR");
        extintor->estado = 0;
        extintor->es_extintor = 1;
        extintor->turnos_elaboracion = 0;
        extintor->prob_incendio = 0;

        juego->inventario[0] = extintor;

        // Reubicar estación 'E'
        int nuevo_x, nuevo_y;
        do {
            nuevo_x = rand() % tablero->columnas;
            nuevo_y = rand() % tablero->filas;
        } while (tablero->celdas[nuevo_y][nuevo_x] != NULL);

        // Mover la estación
        tablero->celdas[y][x] = NULL;
        tablero->celdas[nuevo_y][nuevo_x] = est;

        printf("¡Recolectaste el extintor! Inventario vaciado. Estación de extintor movida a (%d, %d).\n", nuevo_x, nuevo_y);
        return;
    }

    // Caso 2: apagar incendio si se está en fuego y se tiene extintor
    if (est->simbolo == 'F' && tiene_extintor) {
        est->en_llamas = 0;
        est->turnos_inhabilitada = 2;
        est->simbolo = 'C';
        est->accion = cocinar;
        printf("¡Incendio apagado exitosamente!\n");

        // Quitar extintor del inventario
        for (int i = 0; i < 5; i++) {
            if (juego->inventario[i] && juego->inventario[i]->es_extintor == 1) {
                free(juego->inventario[i]);
                juego->inventario[i] = NULL;
                break;
            }
        }
        return;
    }

    // Ninguna de las dos condiciones cumplidas
    if (est->simbolo == 'F') {
        printf("¡Necesitas un extintor para apagar el incendio!\n");
    } else {
        printf("No hay incendio ni extintor en esta estación.\n");
    }
}


// void apagar_incendio(void* contexto, int x, int y) {
//     Juego* juego = (Juego*)contexto;
//     Tablero* tablero = juego->tablero;

//     Estacion* est = (Estacion*)tablero->celdas[y][x];

//     if (est->en_llamas) {
//         printf("¡Usaste el extintor y apagaste el incendio!\n");
//         est->en_llamas = 0;
//         est->turnos_inhabilitada = 2;
//         est->simbolo = 'C'; 

//     } else {
//         printf("No hay incendio en esta estación.\n");
//     }


// }