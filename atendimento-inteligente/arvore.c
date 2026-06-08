#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

/* =============================================
   Implementação da Árvore Binária de Busca
   ============================================= */

void arvore_inicializar(Arvore *a)
{
    a->raiz    = NULL;
    a->tamanho = 0;
}


static NoArvore *criar_no(Atendimento at)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (!no) return NULL;
    no->dado      = at;
    no->esquerda  = NULL;
    no->direita   = NULL;
    return no;
}

static NoArvore *inserir_rec(NoArvore *raiz, Atendimento at, int *ok)
{
    if (!raiz) {
        *ok = 1;
        return criar_no(at);
    }
    if (at.id < raiz->dado.id)
        raiz->esquerda = inserir_rec(raiz->esquerda, at, ok);
    else if (at.id > raiz->dado.id)
        raiz->direita  = inserir_rec(raiz->direita,  at, ok);
    else
        *ok = 0; 
    return raiz;
}

static NoArvore *buscar_rec(NoArvore *raiz, int id)
{
    if (!raiz)             return NULL;
    if (id == raiz->dado.id) return raiz;
    if (id < raiz->dado.id)  return buscar_rec(raiz->esquerda, id);
    return buscar_rec(raiz->direita, id);
}

static void em_ordem_rec(const NoArvore *raiz)
{
    if (!raiz) return;
    em_ordem_rec(raiz->esquerda);
    atendimento_exibir(&raiz->dado);
    em_ordem_rec(raiz->direita);
}

static void destruir_rec(NoArvore *raiz)
{
    if (!raiz) return;
    destruir_rec(raiz->esquerda);
    destruir_rec(raiz->direita);
    free(raiz);
}

static NoArvore *minimo(NoArvore *raiz)
{
    while (raiz->esquerda)
        raiz = raiz->esquerda;
    return raiz;
}

static NoArvore *remover_rec(NoArvore *raiz, int id, int *ok)
{
    if (!raiz) { *ok = 0; return NULL; }

    if (id < raiz->dado.id) {
        raiz->esquerda = remover_rec(raiz->esquerda, id, ok);
    } else if (id > raiz->dado.id) {
        raiz->direita  = remover_rec(raiz->direita,  id, ok);
    } else {
        *ok = 1;
        if (!raiz->esquerda && !raiz->direita) {
            free(raiz);
            return NULL;
        }
        if (!raiz->esquerda) {
            NoArvore *tmp = raiz->direita;
            free(raiz);
            return tmp;
        }
        if (!raiz->direita) {
            NoArvore *tmp = raiz->esquerda;
            free(raiz);
            return tmp;
        }
        NoArvore *suc = minimo(raiz->direita);
        raiz->dado    = suc->dado;
        int dummy = 0;
        raiz->direita = remover_rec(raiz->direita, suc->dado.id, &dummy);
    }
    return raiz;
}

int arvore_inserir(Arvore *a, Atendimento at)
{
    int ok = 0;
    a->raiz = inserir_rec(a->raiz, at, &ok);
    if (ok) a->tamanho++;
    return ok;
}

Atendimento *arvore_buscar(Arvore *a, int id)
{
    NoArvore *no = buscar_rec(a->raiz, id);
    return no ? &no->dado : NULL;
}

int arvore_atualizar_status(Arvore *a, int id, const char *novo_status)
{
    NoArvore *no = buscar_rec(a->raiz, id);
    if (!no) return 0;
    strncpy(no->dado.status, novo_status, sizeof(no->dado.status) - 1);
    no->dado.status[sizeof(no->dado.status) - 1] = '\0';
    return 1;
}

void arvore_em_ordem(const Arvore *a)
{
    if (!a->raiz) {
        printf("  [Arvore vazia]\n");
        return;
    }
    em_ordem_rec(a->raiz);
}

int arvore_remover(Arvore *a, int id)
{
    int ok = 0;
    a->raiz = remover_rec(a->raiz, id, &ok);
    if (ok) a->tamanho--;
    return ok;
}

void arvore_destruir(Arvore *a)
{
    destruir_rec(a->raiz);
    a->raiz    = NULL;
    a->tamanho = 0;
}