#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

No* criarNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (!novo) { fprintf(stderr, "Erro ao alocar memoria\n"); exit(1); }
    novo->valor = valor;
    novo->esq   = NULL;
    novo->dir   = NULL;
    return novo;
}

No* inserirNaArvore(No *raiz, int valor) {
    if (raiz == NULL)
        return criarNo(valor);
    if (valor < raiz->valor)
        raiz->esq = inserirNaArvore(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserirNaArvore(raiz->dir, valor);
    return raiz;
}

int buscarNaArvore(No *raiz, int valor, int *comparacoes) {
    if (raiz == NULL) { (*comparacoes)++; return 0; }
    (*comparacoes)++;
    if (valor == raiz->valor) return 1;
    if (valor < raiz->valor)
        return buscarNaArvore(raiz->esq, valor, comparacoes);
    return buscarNaArvore(raiz->dir, valor, comparacoes);
}

int alturaArvore(No *raiz) {
    if (raiz == NULL) return 0;
    int esq = alturaArvore(raiz->esq);
    int dir = alturaArvore(raiz->dir);
    return 1 + (esq > dir ? esq : dir);
}

void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

static void _exportarNos(No *raiz, FILE *f) {
    if (raiz == NULL) return;
    if (raiz->esq) { fprintf(f, "    %d -> %d;\n", raiz->valor, raiz->esq->valor); _exportarNos(raiz->esq, f); }
    if (raiz->dir) { fprintf(f, "    %d -> %d;\n", raiz->valor, raiz->dir->valor); _exportarNos(raiz->dir, f); }
}

void exportarDOT(No *raiz, const char *arquivo) {
    FILE *f = fopen(arquivo, "w");
    if (!f) { fprintf(stderr, "Erro ao criar arquivo DOT\n"); return; }
    fprintf(f, "digraph Arvore {\n");
    _exportarNos(raiz, f);
    fprintf(f, "}\n");
    fclose(f);
    printf("Arvore exportada para %s\n", arquivo);
}