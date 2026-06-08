#ifndef FILA_H
#define FILA_H

#include "atendimento.h"

/* =============================================
   TAD Fila Dinâmica (FIFO)
   Controla a ordem de atendimento.
   Cada nó aloca memória dinamicamente.
   ============================================= */

typedef struct NoFila {
    Atendimento dado;
    struct NoFila *proximo;
} NoFila;

typedef struct {
    NoFila *frente;
    NoFila *tras;
    int tamanho;
} Fila;

void fila_inicializar(Fila *f);

int fila_vazia(const Fila *f);

int fila_enfileirar(Fila *f, Atendimento a);

int fila_desenfileirar(Fila *f, Atendimento *dest);

int fila_frente(const Fila *f, Atendimento *dest);

void fila_listar(const Fila *f);

void fila_destruir(Fila *f);

int fila_remover_por_id(Fila *f, int id);

#endif 