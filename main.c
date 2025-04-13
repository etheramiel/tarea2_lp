#include <stdio.h>
#include <stdlib.h>

int main(){
    int *a = (int *)malloc(sizeof(int));
    *a = 2;
    printf("%d", *a);
    free(a);
    return 0;

}