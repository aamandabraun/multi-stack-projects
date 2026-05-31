#include <stdlib.h>
#include "buscas.h"

int buscaSequencial(int vetor[], int tamanho, int valor, int *comparacoes) {
    for (int i = 0; i < tamanho; i++) {
        (*comparacoes)++;
        if (vetor[i] == valor)
            return i;
    }
    return -1;
}

int buscaBinaria(int vetor[], int tamanho, int valor, int *comparacoes) {
    int inicio = 0, fim = tamanho - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        (*comparacoes)++;
        if (vetor[meio] == valor) return meio;
        if (vetor[meio] < valor) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

static int comparar(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void ordenarVetor(int vetor[], int tamanho) {
    qsort(vetor, tamanho, sizeof(int), comparar);
}