#ifndef ARVORE_H
#define ARVORE_H

#include "atendimento.h"

/* =============================================
   TAD Árvore Binária de Busca (BST)
   Permite busca por ID em O(log n) médio.
   Cada nó armazena uma cópia do atendimento.
   ============================================= */

typedef struct NoArvore {
    Atendimento dado;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

typedef struct {
    NoArvore *raiz;
    int tamanho;
} Arvore;

void arvore_inicializar(Arvore *a);

int arvore_inserir(Arvore *a, Atendimento at);

Atendimento *arvore_buscar(Arvore *a, int id);

int arvore_atualizar_status(Arvore *a, int id, const char *novo_status);

void arvore_em_ordem(const Arvore *a);

int arvore_remover(Arvore *a, int id);

void arvore_destruir(Arvore *a);

#endif 