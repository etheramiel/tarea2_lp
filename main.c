#include <stdio.h>
#include <stdlib.h>

#include "acciones.h"
#include "tablero.h"
#include "inventario.h"
#include "main.h"


//tablero.c

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
    }else if (dificultad == 2){
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

