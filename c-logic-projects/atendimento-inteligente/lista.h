#ifndef LISTA_H
#define LISTA_H

#include "atendimento.h"

/* =============================================
   TAD Lista Encadeada Simples
   Mantém o histórico de todos os atendimentos
   cadastrados no sistema.
   ============================================= */

typedef struct NoLista {
    Atendimento dado;
    struct NoLista *proximo;
} NoLista;

typedef struct {
    NoLista *cabeca;
    int tamanho;
} Lista;

void lista_inicializar(Lista *l);

int lista_inserir(Lista *l, Atendimento a);

void lista_listar(const Lista *l);

int lista_buscar_por_cliente(const Lista *l, const char *nome);

int lista_buscar_por_prioridade(const Lista *l, int prioridade);

int lista_alterar_status(Lista *l, int id, const char *novo_status);

Atendimento *lista_buscar_por_id(Lista *l, int id);

int lista_tamanho(const Lista *l);

void lista_destruir(Lista *l);

#endif 