#include <stdio.h>

void redimensionar() {
    int *vetor = (int *) malloc(2 * sizeof(int));
    vetor[0] = 10; vetor[1] = 20;

    int *temp = (int *) realloc(vetor, 4 * sizeof(int));
    if (temp != NULL) {
        vetor = temp;
        vetor[2] = 30; vetor[3] = 40;
    }
    free(vetor);
}