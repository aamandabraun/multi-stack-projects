#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

/* =============================================
   Implementação da Fila Dinâmica (FIFO)
   ============================================= */

void fila_inicializar(Fila *f)
{
    f->frente   = NULL;
    f->tras     = NULL;
    f->tamanho  = 0;
}

int fila_vazia(const Fila *f)
{
    return f->frente == NULL;
}

int fila_enfileirar(Fila *f, Atendimento a)
{
    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    if (!novo) {
        fprintf(stderr, "Erro: falha ao alocar no da fila.\n");
        return 0;
    }
    novo->dado     = a;
    novo->proximo  = NULL;

    if (fila_vazia(f)) {
        f->frente = novo;
        f->tras   = novo;
    } else {
        f->tras->proximo = novo;
        f->tras          = novo;
    }
    f->tamanho++;
    return 1;
}

int fila_desenfileirar(Fila *f, Atendimento *dest)
{
    if (fila_vazia(f)) {
        printf("Fila vazia. Nenhum atendimento para processar.\n");
        return 0;
    }
    NoFila *removido = f->frente;
    *dest            = removido->dado;
    f->frente        = removido->proximo;
    if (f->frente == NULL)
        f->tras = NULL;
    free(removido);
    f->tamanho--;
    return 1;
}

int fila_frente(const Fila *f, Atendimento *dest)
{
    if (fila_vazia(f)) return 0;
    *dest = f->frente->dado;
    return 1;
}

void fila_listar(const Fila *f)
{
    if (fila_vazia(f)) {
        printf("  [Fila de espera vazia]\n");
        return;
    }
    NoFila *atual = f->frente;
    int pos = 1;
    while (atual) {
        printf("  Posicao %d:\n", pos++);
        atendimento_exibir(&atual->dado);
        atual = atual->proximo;
    }
}

int fila_remover_por_id(Fila *f, int id)
{
    if (fila_vazia(f)) return 0;

    NoFila *atual    = f->frente;
    NoFila *anterior = NULL;

    while (atual) {
        if (atual->dado.id == id) {
            if (anterior)
                anterior->proximo = atual->proximo;
            else
                f->frente = atual->proximo;

            if (atual == f->tras)
                f->tras = anterior;

            free(atual);
            f->tamanho--;
            return 1;
        }
        anterior = atual;
        atual    = atual->proximo;
    }
    return 0;
}

void fila_destruir(Fila *f)
{
    NoFila *atual = f->frente;
    while (atual) {
        NoFila *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    f->frente  = NULL;
    f->tras    = NULL;
    f->tamanho = 0;
}