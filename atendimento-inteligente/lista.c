#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"

/* =============================================
   Implementação da Lista Encadeada (Histórico)
   ============================================= */

void lista_inicializar(Lista *l)
{
    l->cabeca   = NULL;
    l->tamanho  = 0;
}

int lista_inserir(Lista *l, Atendimento a)
{
    NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
    if (!novo) {
        fprintf(stderr, "Erro: falha ao alocar no da lista.\n");
        return 0;
    }
    novo->dado     = a;
    novo->proximo  = NULL;

    if (l->cabeca == NULL) {
        l->cabeca = novo;
    } else {
        NoLista *atual = l->cabeca;
        while (atual->proximo)
            atual = atual->proximo;
        atual->proximo = novo;
    }
    l->tamanho++;
    return 1;
}

void lista_listar(const Lista *l)
{
    if (l->cabeca == NULL) {
        printf("  [Historico vazio]\n");
        return;
    }
    NoLista *atual = l->cabeca;
    int i = 1;
    while (atual) {
        printf("  Registro %d:\n", i++);
        atendimento_exibir(&atual->dado);
        atual = atual->proximo;
    }
}

static void str_tolower(const char *src, char *dest, int max)
{
    int i;
    for (i = 0; i < max - 1 && src[i]; i++)
        dest[i] = (char)tolower((unsigned char)src[i]);
    dest[i] = '\0';
}

int lista_buscar_por_cliente(const Lista *l, const char *nome)
{
    int encontrados = 0;
    char nomeBusca[50], nomeAtual[50];
    str_tolower(nome, nomeBusca, sizeof(nomeBusca));

    NoLista *atual = l->cabeca;
    while (atual) {
        str_tolower(atual->dado.cliente, nomeAtual, sizeof(nomeAtual));
        if (strstr(nomeAtual, nomeBusca)) {
            atendimento_exibir(&atual->dado);
            encontrados++;
        }
        atual = atual->proximo;
    }
    return encontrados;
}

int lista_buscar_por_prioridade(const Lista *l, int prioridade)
{
    int encontrados = 0;
    NoLista *atual = l->cabeca;
    while (atual) {
        if (atual->dado.prioridade == prioridade) {
            atendimento_exibir(&atual->dado);
            encontrados++;
        }
        atual = atual->proximo;
    }
    return encontrados;
}

int lista_alterar_status(Lista *l, int id, const char *novo_status)
{
    NoLista *atual = l->cabeca;
    while (atual) {
        if (atual->dado.id == id) {
            strncpy(atual->dado.status, novo_status, sizeof(atual->dado.status) - 1);
            atual->dado.status[sizeof(atual->dado.status) - 1] = '\0';
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

Atendimento *lista_buscar_por_id(Lista *l, int id)
{
    NoLista *atual = l->cabeca;
    while (atual) {
        if (atual->dado.id == id)
            return &atual->dado;
        atual = atual->proximo;
    }
    return NULL;
}

int lista_tamanho(const Lista *l)
{
    return l->tamanho;
}

void lista_destruir(Lista *l)
{
    NoLista *atual = l->cabeca;
    while (atual) {
        NoLista *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    l->cabeca  = NULL;
    l->tamanho = 0;
}