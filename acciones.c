#include <stdio.h>
#include "acciones.h"



void cocinar(void* contexto, int x, int y) {
    Tablero* tablero = juego->tablero;

    printf("Ingredientes en inventario")
}

void cortar(void* contexto, int x, int y) {
    printf("Acción: cortar en (%d, %d)\n", x, y);
}

void buscar_ingrediente(void* contexto, int x, int y) {
    printf("Acción: buscar ingrediente en (%d, %d)\n", x, y);
}

void apagar_incendio(void* contexto, int x, int y) {
    printf("Acción: apagar incendio en (%d, %d)\n", x, y);
}

void entregar_pedido(void* contexto) {
    printf("Acción: entregar pedido\n");
}
