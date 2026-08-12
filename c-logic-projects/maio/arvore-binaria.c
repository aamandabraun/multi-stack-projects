#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No *criar_no(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No *inserir(No *raiz, int valor) {
    if (raiz == NULL)
        return criar_no(valor);
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

No *buscar(No *raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor)
        return raiz;
    if (valor < raiz->valor)
        return buscar(raiz->esq, valor);
    return buscar(raiz->dir, valor);
}

No *menor_no(No *no) {
    while (no->esq != NULL)
        no = no->esq;
    return no;
}

No *remover(No *raiz, int valor) {
    if (raiz == NULL)
        return NULL;
    if (valor < raiz->valor)
        raiz->esq = remover(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = remover(raiz->dir, valor);
    else {
        if (raiz->esq == NULL) {
            No *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        No *temp = menor_no(raiz->dir);
        raiz->valor = temp->valor;
        raiz->dir = remover(raiz->dir, temp->valor);
    }
    return raiz;
}

void derrubar(No *raiz) {
    if (raiz == NULL)
        return;
    derrubar(raiz->esq);
    derrubar(raiz->dir);
    free(raiz);
}

void imprimir_em_ordem(No *raiz) {
    if (raiz == NULL)
        return;
    imprimir_em_ordem(raiz->esq);
    printf("%d ", raiz->valor);
    imprimir_em_ordem(raiz->dir);
}

int main() {
    No *raiz = NULL;

    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    printf("Arvore em ordem: ");
    imprimir_em_ordem(raiz);
    printf("\n");

    No *encontrado = buscar(raiz, 40);
    if (encontrado)
        printf("Valor %d encontrado!\n", encontrado->valor);
    else
        printf("Valor nao encontrado.\n");

    raiz = remover(raiz, 30);
    printf("Arvore apos remover 30: ");
    imprimir_em_ordem(raiz);
    printf("\n");

    derrubar(raiz);
    raiz = NULL;
    printf("Arvore derrubada.\n");

    return 0;
}
