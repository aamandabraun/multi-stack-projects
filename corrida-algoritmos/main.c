#include "utils.h"
#include "ordenacao.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main() {
    int n = 100;
    Aluno *vetor = malloc(n * sizeof(Aluno));

    if (!vetor) {
        printf("Erro de memoria\n");
        return 1;
    }

    srand(time(NULL));

    // ================= ALEATÓRIO =================
    gerarAleatorio(vetor, n);

    resetarContadores();
    bubbleSort(vetor, n);
    printf("Bubble (Aleatorio) -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    gerarAleatorio(vetor, n);
    resetarContadores();
    selectionSort(vetor, n);
    printf("Selection (Aleatorio) -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    gerarAleatorio(vetor, n);
    resetarContadores();
    insertionSort(vetor, n);
    printf("Insertion (Aleatorio) -> Comp: %d | Trocas: %d\n\n", comparacoes, trocas);


    // ================= ORDENADO =================
    gerarOrdenado(vetor, n);

    resetarContadores();
    bubbleSort(vetor, n);
    printf("Bubble (Ordenado) -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    gerarOrdenado(vetor, n);
    resetarContadores();
    selectionSort(vetor, n);
    printf("Selection (Ordenado) -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    gerarOrdenado(vetor, n);
    resetarContadores();
    insertionSort(vetor, n);
    printf("Insertion (Ordenado) -> Comp: %d | Trocas: %d\n\n", comparacoes, trocas);


    // ================= INVERSO =================
    gerarInverso(vetor, n);

    resetarContadores();
    bubbleSort(vetor, n);
    printf("Bubble (Inverso) -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    gerarInverso(vetor, n);
    resetarContadores();
    selectionSort(vetor, n);
    printf("Selection (Inverso) -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    gerarInverso(vetor, n);
    resetarContadores();
    insertionSort(vetor, n);
    printf("Insertion (Inverso) -> Comp: %d | Trocas: %d\n", comparacoes, trocas);

    free(vetor);

    return 0;
}