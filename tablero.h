#ifndef TABLERO_H
#define TABLERO_H


typedef struct {
    void *** celdas ; // Matriz 2 D de elementos ( puntero triple)
    int filas ;
    int columnas ;
} Tablero ;

void inicializarTablero ( Tablero * tablero , int filas , int columnas);
void mostrarTablero (Tablero* tablero) ;
void actualizarCelda ( Tablero * tablero , int x , int y , void *elemento );

#endif