#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Nodo* criar_nodo(int valor) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo) {
        novo->valor = valor;
        novo->anterior = NULL;
        novo->proximo = NULL;
    }
    return novo;
}

int obter_valor(Nodo *nodo) { return nodo->valor; }
void definir_valor(Nodo *nodo, int valor) { nodo->valor = valor; }
Nodo* obter_anterior(Nodo *nodo) { return nodo->anterior; }
Nodo* obter_proximo(Nodo *nodo) { return nodo->proximo; }
void definir_anterior(Nodo *nodo, Nodo *ant) { nodo->anterior = ant; }
void definir_proximo(Nodo *nodo, Nodo *prox) { nodo->proximo = prox; }
void destruir_nodo(Nodo *nodo) { free(nodo); }

Lista* criar_lista() {
    Lista *l = (Lista*) malloc(sizeof(Lista));
    if (l) {
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
    }
    return l;
}

int esta_vazia(Lista *lista) { return lista->tamanho == 0; }
int tamanho_lista(Lista *lista) { return lista->tamanho; }

void destruir_lista(Lista *lista) {
    Nodo *atual = lista->inicio;
    while (atual != NULL) {
        Nodo *prox = atual->proximo;
        destruir_nodo(atual);
        atual = prox;
    }
    free(lista);
}

int inserir_inicio(Lista *lista, int valor) {
    Nodo *novo = criar_nodo(valor);
    if (!novo) return 0;
    if (esta_vazia(lista)) {
        lista->fim = novo;
    } else {
        novo->proximo = lista->inicio;
        lista->inicio->anterior = novo;
    }
    lista->inicio = novo;
    lista->tamanho++;
    return 1;
}

int inserir_fim(Lista *lista, int valor) {
    Nodo *novo = criar_nodo(valor);
    if (!novo) return 0;
    if (esta_vazia(lista)) {
        lista->inicio = novo;
    } else {
        novo->anterior = lista->fim;
        lista->fim->proximo = novo;
    }
    lista->fim = novo;
    lista->tamanho++;
    return 1;
}

void imprimir_inicio_fim(Lista *lista) {
    Nodo *atual = lista->inicio;
    while (atual) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

void imprimir_fim_inicio(Lista *lista) {
    Nodo *atual = lista->fim;
    while (atual) {
        printf("%d ", atual->valor);
        atual = atual->anterior;
    }
    printf("\n");
}

int remover_inicio(Lista *lista, int *valor_removido) {
    if (esta_vazia(lista)) return 0;
    Nodo *aux = lista->inicio;
    *valor_removido = aux->valor;
    lista->inicio = aux->proximo;
    if (lista->inicio == NULL) {
        lista->fim = NULL;
    } else {
        lista->inicio->anterior = NULL;
    }
    destruir_nodo(aux);
    lista->tamanho--;
    return 1;
}

int remover_fim(Lista *lista, int *valor_removido) {
    if (esta_vazia(lista)) return 0;
    Nodo *aux = lista->fim;
    *valor_removido = aux->valor;
    lista->fim = aux->anterior;
    if (lista->fim == NULL) {
        lista->inicio = NULL;
    } else {
        lista->fim->proximo = NULL;
    }
    destruir_nodo(aux);
    lista->tamanho--;
    return 1;
}

Nodo* buscar(Lista *lista, int valor) {
    Nodo *atual = lista->inicio;
    while (atual) {
        if (atual->valor == valor) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

int inserir_posicao(Lista *lista, int valor, int posicao) {
    if (posicao < 0 || posicao > lista->tamanho) return 0;
    if (posicao == 0) return inserir_inicio(lista, valor);
    if (posicao == lista->tamanho) return inserir_fim(lista, valor);
    Nodo *novo = criar_nodo(valor);
    if (!novo) return 0;
    Nodo *atual = lista->inicio;
    for (int i = 0; i < posicao; i++) atual = atual->proximo;
    novo->proximo = atual;
    novo->anterior = atual->anterior;
    atual->anterior->proximo = novo;
    atual->anterior = novo;
    lista->tamanho++;
    return 1;
}

int remover_valor(Lista *lista, int valor) {
    Nodo *alvo = buscar(lista, valor);
    if (!alvo) return 0;
    if (alvo == lista->inicio) {
        int lixo;
        return remover_inicio(lista, &lixo);
    }
    if (alvo == lista->fim) {
        int lixo;
        return remover_fim(lista, &lixo);
    }
    alvo->anterior->proximo = alvo->proximo;
    alvo->proximo->anterior = alvo->anterior;
    destruir_nodo(alvo);
    lista->tamanho--;
    return 1;
}