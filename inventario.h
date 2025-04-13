void crearInventario () ;
void agregarIngrediente () ;
void eliminarIngrediente () ;
void verInventario () ;

typedef struct {
    char nombre [30]; // Ej : " pan " , " pollo "
    int estado ; // Ej : "0 = crudo " , "1 = cortado " , etc .
    int es_extintor ; // 1 si es extintor , 0 si es ingrediente.
    int turnos_elaboracion ; // Turnos que tarda en prepararse .
    int prob_incendio ; // Probabilidad de causar incendio .
} Ingrediente ;

