#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "arvore.h"
#include "buscas.h"

void preencherOrdenado(int v[], long n) {
    for (long i = 0; i < n; i++)
        v[i] = (int)(i + 1);
}

void embaralhar(int v[], long n) {
    for (long i = n - 1; i > 0; i--) {
        long j = rand() % (i + 1);
        int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }
}

No* construirArvore(int v[], long n) {
    No *raiz = NULL;
    for (long i = 0; i < n; i++)
        raiz = inserirNaArvore(raiz, v[i]);
    return raiz;
}

void executarExperimento(long tamanho, int embaralhado, FILE *csv) {
    const char *tipo = embaralhado ? "Embaralhado" : "Ordenado";
    printf("\n=== Experimento: n=%ld | %s ===\n", tamanho, tipo);

    int *base   = NULL;
    int *vetSeq = NULL;
    int *vetBin = NULL;

    base = (int*) malloc(tamanho * sizeof(int));
    if (!base) { fprintf(stderr, "Memoria insuficiente\n"); return; }
    preencherOrdenado(base, tamanho);
    if (embaralhado) embaralhar(base, tamanho);

    vetSeq = (int*) malloc(tamanho * sizeof(int));
    vetBin = (int*) malloc(tamanho * sizeof(int));
    if (!vetSeq || !vetBin) { free(base); free(vetSeq); free(vetBin); return; }
    memcpy(vetSeq, base, tamanho * sizeof(int));
    memcpy(vetBin, base, tamanho * sizeof(int));
    ordenarVetor(vetBin, tamanho);

    No *raiz = construirArvore(base, tamanho);
    int alt = alturaArvore(raiz);
    printf("Altura da arvore: %d\n", alt);

    long alvos[4];
    alvos[0] = (long)(tamanho * 0.01) + 1;
    alvos[1] = (long)(tamanho * 0.50);
    alvos[2] = (long)(tamanho * 0.99);
    alvos[3] = tamanho + 1;

    const char *labels[4] = {"inicio", "meio", "fim", "inexistente"};

    printf("%-15s %10s %12s %12s %10s\n",
           "Valor buscado", "Posicao", "Seq(comp)", "Bin(comp)", "Arv(comp)");
    printf("%-15s %10s %12s %12s %10s\n",
           "-------------", "-------", "---------", "---------", "---------");

    for (int i = 0; i < 4; i++) {
        int valor = (int) alvos[i];
        int cSeq = 0, cBin = 0, cArv = 0;
        clock_t t0, t1;
        double tSeq, tBin, tArv;

        t0 = clock();
        buscaSequencial(vetSeq, (int)tamanho, valor, &cSeq);
        t1 = clock();
        tSeq = (double)(t1 - t0) / CLOCKS_PER_SEC;

        t0 = clock();
        buscaBinaria(vetBin, (int)tamanho, valor, &cBin);
        t1 = clock();
        tBin = (double)(t1 - t0) / CLOCKS_PER_SEC;

        t0 = clock();
        buscarNaArvore(raiz, valor, &cArv);
        t1 = clock();
        tArv = (double)(t1 - t0) / CLOCKS_PER_SEC;

        printf("%-15d %10s %12d %12d %10d\n", valor, labels[i], cSeq, cBin, cArv);

        fprintf(csv, "%ld,%s,%d,%s,%d,%d,%d,%d,%.6f,%.6f,%.6f\n",
                tamanho, tipo, valor, labels[i],
                cSeq, cBin, cArv, alt,
                tSeq, tBin, tArv);
    }

    free(base);
    free(vetSeq);
    free(vetBin);
    liberarArvore(raiz);
}

int main(void) {
    srand((unsigned)time(NULL));

    FILE *csv = fopen("resultados/resultados.csv", "w");
    if (!csv) { fprintf(stderr, "Erro ao criar CSV\n"); return 1; }
    fprintf(csv, "tamanho,tipo,valor,posicao,seq_comp,bin_comp,arv_comp,altura_arvore,seq_tempo,bin_tempo,arv_tempo\n");

    executarExperimento(100,     0, csv);
    executarExperimento(100,     1, csv);
    executarExperimento(1000000, 0, csv);
    executarExperimento(1000000, 1, csv);

    printf("\n=== Experimentos 5 e 6 (1 bilhao): valores teoricos ===\n");
    printf("Busca sequencial   - ordenado/embaralhado: ate 1.000.000.000 comparacoes\n");
    printf("Busca binaria      - log2(1e9) aprox 30 comparacoes\n");
    printf("Arvore ordenada    - degenerada: ate 1.000.000.000 comparacoes\n");
    printf("Arvore embaralhada - log2(1e9) aprox 30 comparacoes\n");

    long n = 1000000000L;
    fprintf(csv, "%ld,Ordenado,1,inicio,1,1,1,%ld,0,0,0\n", n, n);
    fprintf(csv, "%ld,Ordenado,%ld,fim,%ld,30,%ld,%ld,0,0,0\n", n, n, n, n, n);
    fprintf(csv, "%ld,Embaralhado,1,inicio,1,1,30,30,0,0,0\n", n);
    fprintf(csv, "%ld,Embaralhado,%ld,fim,%ld,30,30,30,0,0,0\n", n, n, n);

    fclose(csv);
    printf("\nResultados salvos em resultados/resultados.csv\n");
    return 0;
}