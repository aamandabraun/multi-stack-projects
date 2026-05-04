#include "utils.h"
#include "ordenacao.h"

int main() {
    int n = 100;
    Aluno vetor[n];

    // --- TESTE BUBBLE SORT (ALEATÓRIO) ---
    gerarAleatorio(vetor, n);
    bubbleSort(vetor, n);
    printf("Bubble Sort (Aleatorio) -> Comparacoes: %d | Trocas: %d\n", comparacoes, trocas);

    // --- TESTE SELECTION SORT (ALEATÓRIO) ---
    gerarAleatorio(vetor, n);
    selectionSort(vetor, n);
    printf("Selection Sort (Aleatorio) -> Comparacoes: %d | Trocas: %d\n", comparacoes, trocas);

    return 0;
}