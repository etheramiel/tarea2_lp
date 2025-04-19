#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <time.h>

#include "acciones.h"
#include "tablero.h"
#include "inventario.h"
#include "main.h"

#define CANTIDAD_PLATOS 5

extern Jugador* jugador;
Juego* juego;
Pedido platos_base[CANTIDAD_PLATOS];

void mostrarPedidoActual(Pedido* pedido, int cant_ingredientes) {
    printf("'%s': [", pedido->nombre_plato);
    for (int i = 0; i < cant_ingredientes; i++) {
        printf("%s", pedido->ingredientes_requeridos[i]->nombre);
        if (i != cant_ingredientes - 1) {
            printf(", ");
        }
    }
    printf("]. \n");
}


void crearMenu(){ // "0 = crudo " , "1 = cortado " , "2 = frito" , "3 = cocinado", "4 = cortado y frito"

    //Crear McChcarly (papas fritas(y coratdas), pollo frito)
    strcpy(platos_base[0].nombre_plato, "el McCharly");
    const char* ingredientes_plato0[] = {"papa", "pollo"};
    int estados0[] = {4, 2};
    platos_base[0].completado = 0;
    platos_base[0].ingredientes_requeridos = malloc(2 * sizeof(Ingrediente*));
    for(int i = 0; i<2; i++){
        platos_base[0].ingredientes_requeridos[i] = malloc(sizeof(Ingrediente));
        strcpy(platos_base[0].ingredientes_requeridos[i]->nombre, ingredientes_plato0[i]);
        platos_base[0].ingredientes_requeridos[i]->estado = estados0[i];
    }

    //Crear Papapleto (papas fritas(y cortadas), tomate, pan)
    strcpy(platos_base[1].nombre_plato, "papaleto");
    const char* ingredientes_plato1[] = {"papa", "tomate", "pan"};
    int estados1[] = {4, 1, 0};
    platos_base[1].completado = 0;
    platos_base[1].ingredientes_requeridos = malloc(3 * sizeof(Ingrediente*));

    for (int i = 0; i < 3; i++) {
        platos_base[1].ingredientes_requeridos[i] = malloc(sizeof(Ingrediente));
        strcpy(platos_base[1].ingredientes_requeridos[i]->nombre, ingredientes_plato1[i]);
        platos_base[1].ingredientes_requeridos[i]->estado = estados1[i];
    }    

    //Crear Pasta a la sansini (pasta, tomate)
    strcpy(platos_base[2].nombre_plato, "Pasta a la sansini");
    const char* ingredientes_plato2[] = {"pasta", "tomate"};
    int estados2[] = {3, 1};
    platos_base[2].completado = 0;
    platos_base[2].ingredientes_requeridos = malloc(2 * sizeof(Ingrediente*));

    for(int i = 0; i<2; i++){
        platos_base[2].ingredientes_requeridos[i] = malloc(sizeof(Ingrediente));
        strcpy(platos_base[2].ingredientes_requeridos[i]->nombre, ingredientes_plato2[i]);
        platos_base[2].ingredientes_requeridos[i]->estado = estados2[i];
    }

    //Crear El Certamen (pan, lechuga, tomate, hamburguesa)
    strcpy(platos_base[3].nombre_plato, "El Certamen");
    const char* ingredientes_plato3[] = {"pan", "lechuga", "tomate", "hamburguesa"};
    int estados3[] = {0, 1, 1, 3};
    platos_base[3].completado = 0;
    platos_base[3].ingredientes_requeridos = malloc(4 * sizeof(Ingrediente*));

    for(int i = 0; i<4; i++){
        platos_base[3].ingredientes_requeridos[i] = malloc(sizeof(Ingrediente));
        strcpy(platos_base[3].ingredientes_requeridos[i]->nombre, ingredientes_plato3[i]);
        platos_base[3].ingredientes_requeridos[i]->estado = estados3[i];
    }


    //Crear El Clasico (arroz, pollo frito)
    strcpy(platos_base[4].nombre_plato, "El Clasico");
    const char* ingredientes_plato4[] = {"arroz", "pollo"};
    int estados4[] = {3, 2};
    platos_base[4].completado = 0;
    platos_base[4].ingredientes_requeridos = malloc(2 * sizeof(Ingrediente*));

    for(int i = 0; i<2; i++){
        platos_base[4].ingredientes_requeridos[i] = malloc(sizeof(Ingrediente));
        strcpy(platos_base[4].ingredientes_requeridos[i]->nombre, ingredientes_plato4[i]);
        platos_base[4].ingredientes_requeridos[i]->estado = estados4[i];
    }

}
//2, 3, 2, 4, 2
void cerrarMenu(){

    for(int i = 0; i<2; i++){
        
        free(platos_base[0].ingredientes_requeridos[i]);
        
    }free(platos_base[0].ingredientes_requeridos);

    for(int i = 0; i<3; i++){
        
        free(platos_base[1].ingredientes_requeridos[i]);
        
    }free(platos_base[1].ingredientes_requeridos);

    for(int i = 0; i<2; i++){
        
        free(platos_base[2].ingredientes_requeridos[i]);
        
    }free(platos_base[2].ingredientes_requeridos);
    
    for(int i = 0; i<4; i++){
        
        free(platos_base[3].ingredientes_requeridos[i]);
        
    }free(platos_base[3].ingredientes_requeridos);

    for(int i = 0; i<2; i++){
        
        free(platos_base[4].ingredientes_requeridos[i]);
        
    }free(platos_base[4].ingredientes_requeridos);


}

// void mostrarMenu() {
//     int cantidad_ingredientes[CANTIDAD_PLATOS] = {2, 3, 2, 4, 2};
//     printf("=== MENÚ BASE ===\n");
//     for (int i = 0; i < CANTIDAD_PLATOS; i++) {
//         printf("Plato %d: %s\n", i + 1, platos_base[i].nombre_plato);
//         printf("  Completado: %s\n", platos_base[i].completado ? "Sí" : "No");

//         // Se asume un máximo razonable de ingredientes por plato (ej: 5)
//         for (int j = 0; j < cantidad_ingredientes[i]; j++) {
//             printf("    Ingrediente: %s | Estado: %d\n",
//                 platos_base[i].ingredientes_requeridos[j]->nombre,
//                 platos_base[i].ingredientes_requeridos[j]->estado);
//         }
//     }
//     printf("=================\n");
// }

int main(){
    srand(time(NULL)); 
    juego = malloc(sizeof(Juego));
    int elegido;

    printf("Seleccione dificultad:\n1.Facil\n2.Medio\n3.Dificil\n");
    int dificultad, filas, columnas, cant_pedidos;
    scanf("%d", &dificultad);
    Tablero* tablero = malloc(sizeof(Tablero));
    juego->tablero = tablero;
    crearInventario();
    crearMenu();
    // mostrarMenu();

    // Ingrediente* i = malloc(sizeof(Ingrediente));
    // strcpy(i->nombre, "pollo");
    // i->estado = 0;
    // i->es_extintor = 0;
    // juego->inventario[0] = i;

    // Ingrediente* i2 = malloc(sizeof(Ingrediente));
    // strcpy(i2->nombre, "papa");
    // i2->estado = 0;
    // i2->es_extintor = 0;
    // juego->inventario[1] = i2;


    if(dificultad == 1){
        filas = columnas = 5;
        cant_pedidos = 3;
        juego->turnos_restantes = 60;
        juego->dificultad = 1;
    }else if (dificultad == 2){
        filas = columnas = 10;
        cant_pedidos = 4;
        juego->turnos_restantes = 60;
        juego->dificultad = 2;
    }else{
        filas = columnas = 10;
        cant_pedidos = 5;
        juego->turnos_restantes = 45;
        juego->dificultad = 3;
    }

    juego->pedidos = malloc(cant_pedidos * sizeof(Pedido));

    int cantidad_ingredientes_por_plato[CANTIDAD_PLATOS] = {2, 3, 2, 4, 2};

    for(int i = 0; i < cant_pedidos; i++){

        int elegido = rand() % CANTIDAD_PLATOS;
    
        Pedido* base = &platos_base[elegido];
        juego->pedidos[i].completado = 0;
        strcpy(juego->pedidos[i].nombre_plato, base->nombre_plato);
    
        int j = cantidad_ingredientes_por_plato[elegido];
        juego->pedidos[i].ingredientes_requeridos = malloc(j * sizeof(Ingrediente*));
    
        for(int k = 0; k < j; k++){
            juego->pedidos[i].ingredientes_requeridos[k] = malloc(sizeof(Ingrediente));
            strcpy(juego->pedidos[i].ingredientes_requeridos[k]->nombre, base->ingredientes_requeridos[k]->nombre);
            juego->pedidos[i].ingredientes_requeridos[k]->estado = base->ingredientes_requeridos[k]->estado;
        }
    }


    
    inicializarTablero(tablero, filas, columnas);

    jugador = malloc(sizeof(Jugador));

    do {
        jugador->x = rand() % filas;
        jugador->y = rand() % columnas;
    } while (tablero->celdas[jugador->y][jugador->x] != NULL);

    // printf("Turnos restantes: %d\n", juego->turnos_restantes);
    // mostrarTablero(tablero);

    while(juego->turnos_restantes > 0 && cant_pedidos > 0){
        char accion;
        int casillas;

        int pedido_actual = -1;
        for (int i = 0; i < cant_pedidos; i++) {
            if (juego->pedidos[i].completado == 0) {
                pedido_actual = i;
                break;
            }
        }

        if (pedido_actual != -1) {
            int cantidad_ingredientes_por_plato[CANTIDAD_PLATOS] = {2, 3, 2, 4, 2};

            Pedido* pedido = &juego->pedidos[pedido_actual];

            int index_plato = -1;
            for (int i = 0; i < CANTIDAD_PLATOS; i++) {
                if (strcmp(platos_base[i].nombre_plato, pedido->nombre_plato) == 0) {
                    index_plato = i;
                    break;
                }
            }

            if (index_plato != -1) {
                mostrarPedidoActual(pedido, cantidad_ingredientes_por_plato[index_plato]);
            }
        }
        printf("Turnos restantes: %d\n", juego->turnos_restantes);
        mostrarTablero(tablero);




        printf("Que desea hacer:\n1.Moverse\n2.Accion\n3.Ver Inventario\n4.Entregar Plato\n5.Salir del juego\n");
        scanf(" %c", &accion);

        if(accion == '1'){
            char direccion;
            printf("Ingrese direccion (W, A, S, D): ");
            scanf(" %c", &direccion);
            direccion = toupper(direccion);
            printf("Ingrese cantidad de casillas: ");
            scanf(" %d", &casillas);
            moverJugador(tablero, casillas, direccion);
            juego->turnos_restantes--;
            printf("===============================================\n");
            printf("Turnos restantes: %d\n", juego->turnos_restantes);
            // mostrarTablero(tablero);

        }else if(accion == '2'){
            if(tablero->celdas[jugador->y][jugador->x] != NULL){
                Estacion* e = (Estacion*)tablero->celdas[jugador->y][jugador->x];
                e->accion(juego, jugador->x, jugador->y);
                printf("===============================================\n");
                printf("Turnos restantes: %d\n", juego->turnos_restantes);
                // mostrarTablero(tablero);
            }

            else{
                printf("No se encuentra en una casilla de accion\n");
            }

        }else if(accion == '3'){
            verInventario();
        }else if(accion == '4'){
            entregar_pedido(juego);
        }else if(accion == '5'){
            break;
        }
        for (int i = 0; i < tablero->filas; i++) {
            for (int j = 0; j < tablero->columnas; j++) {
                if (tablero->celdas[i][j] != NULL) {
                    Estacion* est = (Estacion*)tablero->celdas[i][j];
        
                    if (est->turnos_inhabilitada > 0) {
                        est->turnos_inhabilitada--;
        
                        if (est->turnos_inhabilitada == 0 && est->simbolo == 'C') {
                            printf("La cocina en (%d, %d) ha sido restaurada y vuelve a estar operativa.\n", j, i);
                            // Nada más que hacer, ya tiene símbolo correcto
                        }
                    }
                }
            }
        }
    }
    cerrarTablero(tablero);
    liberarInventario();
    free(jugador);
    free(juego);
    free(tablero);
    cerrarMenu();
    //Hacer funcion
    for (int i = 0; i < cant_pedidos; i++) {
        Pedido* p = &juego->pedidos[i];
        for (int j = 0; p->ingredientes_requeridos[j] != NULL; j++) {
            free(p->ingredientes_requeridos[j]);
        }
        free(p->ingredientes_requeridos);
    }
    free(juego->pedidos);
    return 0;   
}

