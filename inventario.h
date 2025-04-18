#ifndef INVENTARIO_H
#define INVENTARIO_H

typedef struct {
    char nombre [30]; // Ej : " pan " , " pollo "
    int estado ; // Ej : "0 = crudo " , "1 = cortado " , "2 = frito" , "3 = cocinado", "4 = cortado y frito"
    int es_extintor ; // 1 si es extintor , 0 si es ingrediente.
    int turnos_elaboracion ; // Turnos que tarda en prepararse .
    int prob_incendio ; // Probabilidad de causar incendio .
} Ingrediente ;

void crearInventario ();
void agregarIngrediente ();
void eliminarIngrediente ();
void verInventario ();
void liberarInventario();

#endif