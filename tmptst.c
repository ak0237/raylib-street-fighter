#include <stdio.h>
#include <stdlib.h>

int main(){

    int max = 5, a;

    int* pointer;

    pointer = malloc((max-1) * sizeof(int));

    for(a = 0; a < max; a++){
        pointer[a] = a;
    }

    free(pointer);

    return 0;
} 